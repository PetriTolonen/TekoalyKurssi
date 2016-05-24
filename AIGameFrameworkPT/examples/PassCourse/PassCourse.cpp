#include "CharacterController.h"
#include "PlayerController.h"
#include "GameEvents.h"

namespace PassCourse
{

	// PassCourseController:
	// Combined behaviour of DirectMoverAI and AutoAttackFlagCarryingBot. This tries to move 
	// to dynamite and if catches the dynamite, goes to enemy home base. If enemy catches the
	// dynamite before, this tries to shoot the enemy.
	class PassCourseController : public CharacterController
	{
	public:
		PassCourseController(yam2d::GameObject* owner, GameController* gameController, BotType botType)
			: CharacterController(owner, gameController, botType)
			// AutoAttackFlagCarryingBot
			, m_gameObjectToShoot(0)
			, m_predictionDistance(0.0f)
			, m_aimTolerance(0.0f)
			// DirectMoverAI
			, m_gameObjectToGo(0)
			, m_reachTolerance(0.0f)
			, m_distanceToDestination(0.0f)
			, m_collisionToHomeBase(false)
		{
		}

		virtual ~PassCourseController(void)
		{
		}

		// AutoAttackFlagCarryingBot

		void setTargetToShoot(const yam2d::GameObject* gameObjectToShoot, float predictionDistance, float aimTolerance)
		{
			m_gameObjectToShoot = gameObjectToShoot;
			m_predictionDistance = predictionDistance;
			m_aimTolerance = aimTolerance;
		}

		void resetTargetToShoot()
		{
			m_gameObjectToShoot = 0;
			m_predictionDistance = 0.0f;
			m_aimTolerance = 0.0f;
		}


		// This virtual method is automatically called byt map/layer, when update is called from main.cpp
		virtual void update(float deltaTime)
		{
			// Call update to base class
			CharacterController::update(deltaTime);

			// AutoAttackFlagCarryingBot
			if (m_gameObjectToShoot != 0)
			{
				float rotation = m_gameObjectToShoot->getRotation();
				slm::vec2 enemyForwardDir;
				enemyForwardDir.x = cosf(rotation);
				enemyForwardDir.y = sinf(rotation);
				autoUsePrimaryWeapon(m_gameObjectToShoot->getPosition() + m_predictionDistance*enemyForwardDir, m_aimTolerance);
			}

			// DirectMoverAI
			if (m_gameObjectToGo != 0)
			{
				// Move to position
				m_distanceToDestination = moveDirectToPosition(m_gameObjectToGo->getPosition(), m_reachTolerance);
			}

			// If has collided to home base, then drop bomb.
			if (m_collisionToHomeBase)
			{
				// Obly if I has flag
				if (hasItem())
				{
					dropItem1();
				}

				m_collisionToHomeBase = false;
			}
		}

		virtual void onMessage(const std::string& msgName, yam2d::Object* eventObject)
		{
			CharacterController::onMessage(msgName, eventObject);
			if (msgName == "Collision")
			{
				CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*>(eventObject);
				assert(collisionEvent != 0);
				assert(collisionEvent->getMyGameObject() == getGameObject());
				yam2d::GameObject* otherGo = collisionEvent->getOtherGameObject();
				std::string otherType = otherGo->getType();
				if (otherType == "HomeBase")
				{
					if (hasItem())
					{
						dropItem1();
					}
				}
			}
		}

		// DirectMoverAI

		void setMoveTargetObject(const yam2d::GameObject* gameObjectToGo, float reachTolerance)
		{
			if (gameObjectToGo == 0)
			{
				resetMoveTargetObject();
				return;
			}

			m_gameObjectToGo = gameObjectToGo;
			m_reachTolerance = reachTolerance;
			m_distanceToDestination = slm::length(m_gameObjectToGo->getPosition() - getGameObject()->getPosition());
			preferPickItem();
		}

		void resetMoveTargetObject()
		{
			m_gameObjectToGo = 0;
			m_reachTolerance = 0.0f;
			m_distanceToDestination = 0.0f;
			stop();
		}

		float getDistanceToDestination() const
		{
			return m_distanceToDestination;
		}

	private:
		// AutoAttackFlagCarryingBot -behaviour = GOTO_DEFEND_HOME_BASE -state
		const yam2d::GameObject* m_gameObjectToShoot;
		float m_predictionDistance;
		float m_aimTolerance;

		// DirectMoverAI -behaviour = GOTO_ENEMY_BASE and GOTO_DYNAMITE
		const yam2d::GameObject* m_gameObjectToGo;
		float m_reachTolerance;
		float m_distanceToDestination;
		bool m_collisionToHomeBase;

	};

	
	class PassCoursePlayer : public PlayerController
	{
	private:
		std::string m_myTeamName;
		std::vector< yam2d::Ref<PassCourseController> > m_controllers;

	public:
		PassCoursePlayer()
			: PlayerController()
		{
		}

		virtual ~PassCoursePlayer()
		{
		}


		virtual void setMyTeamName(std::string& teamName)
		{
			m_myTeamName = teamName;
		}

		// Called, when bots are spawn. Shall return correct player character controller for bot if given name.
		virtual CharacterController* createPlayerCharacterController(GameController* gameController, yam2d::GameObject* ownerGameObject, const std::string& playerName, BotType type)
		{
			if (playerName == "PassCourse")
			{
				PassCourseController* myAI = new PassCourseController(ownerGameObject, gameController, type);
				m_controllers.push_back(myAI);
				return myAI;
			}
		
			return 0;
		}

		// Called, when bots have spawn. Can be used some custom initialization after spawn.
		virtual void onGameStarted(GameEnvironmentInfoProvider* environmentInfo)
		{
			yam2d::esLogMessage("onGameStarted");
			// Start going straight to dynamite
			const yam2d::GameObject* dynamite = environmentInfo->getDynamite();
			for (size_t i = 0; i < m_controllers.size(); ++i)
			{
				m_controllers[i]->setMoveTargetObject(dynamite, 1.0f);
			}

			// Get speed map...
			/*AIMapLayer* moveSpeedMap = environmentInfo->getAILayer("GroundMoveSpeed");
			for (size_t y = 0; y < moveSpeedMap->getHeight(); ++y)
			{
				for (size_t x = 0; x < moveSpeedMap->getWidth(); ++x)
				{
					// Get pixel from pos x,y. Pixel values are 4 bytes reach color channel (RGBA).
					// Pixel in current implementation is white=[255,255,255,255]/gray=[127,127,127,127]/black=[0,0,0,0])
					// Value = 0 -> Pixel not walkable (0.0x speed)
					// Value = 127 -> Pixel slowly walkable (0.5x speed)
					// Value = 255 -> Pixel fully walkable (1.0x speed)
					uint8_t red = moveSpeedMap->getPixel(x, y)[0];
					uint8_t green = moveSpeedMap->getPixel(x, y)[1];
					uint8_t blue = moveSpeedMap->getPixel(x, y)[2];
					uint8_t alpha = moveSpeedMap->getPixel(x, y)[3];
				}
			}*/
		}


		// Called when game has ended. Can be used some cuystom deinitialization after game.
		virtual void onGameOver(GameEnvironmentInfoProvider* environmentInfo, const std::string& gameResultString)
		{
			yam2d::esLogMessage("onGameOver: %s wins!", gameResultString.c_str());
			for (size_t i = 0; i < m_controllers.size(); ++i)
			{
				m_controllers[i]->resetMoveTargetObject();
				m_controllers[i]->resetTargetToShoot();
			}
		}

		virtual void onUpdate(GameEnvironmentInfoProvider* environmentInfo, float deltaTime)
		{
		}

		virtual void onGameEvent(GameEnvironmentInfoProvider* environmentInfo, const std::string& eventName, yam2d::Object* eventObject)
		{
			if (eventName == "ItemPicked")
			{
				ItemEvent* itemEvent = dynamic_cast<ItemEvent*>(eventObject);
				assert(itemEvent != 0);
				yam2d::GameObject* item = itemEvent->getItemGameObject();
				int teamIndex = itemEvent->getCharacterGameObject()->getProperties()["teamIndex"].get<int>();

				if (teamIndex == getMyTeamIndex())
				{
					yam2d::esLogMessage("My team picked item. Chase enemy HomeBase.");
					const yam2d::GameObject* homeBase = environmentInfo->getEnemyHomeBase(this);
					for (size_t i = 0; i < m_controllers.size(); ++i)
					{
						m_controllers[i]->resetTargetToShoot();
						m_controllers[i]->setMoveTargetObject(homeBase, 1.0f);
					}
				}
				else
				{
					yam2d::esLogMessage("Other team picked item. Stop Moving and Shoot enemy.");
	
					// Stop and Shoot enemy
					for (size_t i = 0; i < m_controllers.size(); ++i)
					{
						m_controllers[i]->resetMoveTargetObject();
						m_controllers[i]->setTargetToShoot(itemEvent->getCharacterController()->getGameObject(), 1.9f, 0.05f);
					}
				}
			}
			else if (eventName == "ItemDropped")
			{
				ItemEvent* itemEvent = dynamic_cast<ItemEvent*>(eventObject);
				assert(itemEvent != 0);
				yam2d::esLogMessage("Item dropped. Stop Shooting and Chase Dynamite.");
				for (size_t i = 0; i < m_controllers.size(); ++i)
				{
					m_controllers[i]->resetTargetToShoot();
				}
				
				// Start going straight to dynamite
				const yam2d::GameObject* dynamite = environmentInfo->getDynamite();
				for (size_t i = 0; i < m_controllers.size(); ++i)
				{
					m_controllers[i]->setMoveTargetObject(dynamite, 1.0f);
				}
			}
			else
			{
				// Ignore rest message ids.
			}
		}

		virtual void onGameObjectEvent(GameEnvironmentInfoProvider* environmentInfo, yam2d::GameObject* gameObject, const std::string& eventName, yam2d::Object* eventObject)
		{
		
		}
	};


	PlayerController* createNewPlayer()
	{
		return new PassCoursePlayer();
	}
}



