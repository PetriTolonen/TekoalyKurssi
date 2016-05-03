// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include "GameApp.h"

#include "ExampleBehaviours.h"
#include "JoystickController.h"
#include "PathFindingApp.h"
#include "slm/vec2.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "PTAI.h"

class MyPlayerController : public PlayerController
{
private:
	std::string m_myTeamName;
	std::vector< yam2d::Ref<PTAI> > m_MyAIControllers;
	std::vector< yam2d::Ref<JoystickController> > m_joystickControllers;
	std::vector< yam2d::Ref<DirectMoverAI> > m_directMoverAIControllers;
	std::vector< yam2d::Ref<AutoAttackFlagCarryingBot> > m_autoAttackFlagCarryingBots;

public:
	MyPlayerController()
		: PlayerController()
	{
	}

	virtual ~MyPlayerController()
	{
	}


	virtual void setMyTeamName(std::string& teamName)
	{
		m_myTeamName = teamName;
	}

	// Called, when bots are spawn. Shall return correct player character controller for bot if given name.
	virtual CharacterController* createPlayerCharacterController(GameController* gameController, yam2d::GameObject* ownerGameObject, const std::string& playerName, BotType type)
	{
		if (playerName == "JoystickController")
		{
			//if (m_joystickControllers.size()==0) // If only 1 joystick supported.
			{
				JoystickController* joystickController = new JoystickController(ownerGameObject, gameController, type, m_joystickControllers.size());
				m_joystickControllers.push_back(joystickController);
				return joystickController;
			}
		}

		if (playerName == "CharacterController")
		{
			return new CharacterController(ownerGameObject, gameController, type);
		}

		if (playerName == "PTAI")
		{
			PTAI* PtAI = new PTAI(ownerGameObject, gameController, type);
			m_MyAIControllers.push_back(PtAI);
			return PtAI;
		}

		if (playerName == "DirectMoverAI")
		{
			DirectMoverAI* controller = new DirectMoverAI(ownerGameObject, gameController, type);
			m_directMoverAIControllers.push_back(controller);
			return controller;
		}
		
		if (playerName == "AutoAttackFlagCarryingBot")
		{
			AutoAttackFlagCarryingBot* controller = new AutoAttackFlagCarryingBot(ownerGameObject, gameController, type);
			m_autoAttackFlagCarryingBots.push_back(controller);
			return controller;
		}
		return 0;
	}

	// Called, when bots have spawn. Can be used some custom initialization after spawn.
	virtual void onGameStarted(GameEnvironmentInfoProvider* environmentInfo)
	{
		yam2d::esLogMessage("onGameStarted");
		// Start going straight to dynamite
		const yam2d::GameObject* dynamite = environmentInfo->getDynamite();
		for (size_t i = 0; i < m_directMoverAIControllers.size(); ++i)
		{
			m_directMoverAIControllers[i]->setMoveTargetObject(dynamite, 1.0f);
		}

		AIMapLayer* debugMap = environmentInfo->getAILayer("debug");
		uint8_t TP_PIXEL[4] = { 0x00, 0x00, 0x00, 0x00 };
		for (size_t y = 0; y < debugMap->getHeight(); ++y)
		{
			for (size_t x = 0; x < debugMap->getWidth(); ++x)
			{
				debugMap->setPixel(x, y, TP_PIXEL);
			}
		}

		AIMapLayer* moveMap = environmentInfo->getAILayer("GroundMoveSpeed");

		for (size_t i = 0; i < m_MyAIControllers.size(); ++i)
		{
			m_MyAIControllers[i]->setMoveTargetObject(dynamite, 1.0f);
			m_MyAIControllers[i]->setDebugLayer(debugMap);
			m_MyAIControllers[i]->setMoveSpeedLayer(moveMap);
			m_MyAIControllers[i]->setNewPath();
			m_MyAIControllers[i]->startMoving();
		}		
	}


	// Called when game has ended. Can be used some cuystom deinitialization after game.
	virtual void onGameOver(GameEnvironmentInfoProvider* environmentInfo, const std::string& gameResultString)
	{
		yam2d::esLogMessage("onGameOver: %s wins!", gameResultString.c_str());
		for (size_t i = 0; i < m_directMoverAIControllers.size(); ++i)
		{
			m_directMoverAIControllers[i]->resetMoveTargetObject();
		}

		for (size_t i = 0; i < m_autoAttackFlagCarryingBots.size(); ++i)
		{
			m_autoAttackFlagCarryingBots[i]->resetTargetToShoot();
		}

		for (size_t i = 0; i < m_MyAIControllers.size(); ++i)
		{
			m_MyAIControllers[i]->resetMoveTargetObject();
			m_MyAIControllers[i]->resetTargetToShoot();
		}
	}

	// Called each frame. Update you player character controllers in this function.
	virtual void onUpdate(GameEnvironmentInfoProvider* environmentInfo, float deltaTime)
	{
	//	yam2d::esLogMessage("onUpdate");
	}

	// Called, when game event has ocurred.
	// Event name tells the event in question, each event type may have eventObject data associated with the event.
	// 
	// Currently supported eventNames and eventObject data desctiption:
	// - ObjectSpawned:
	//		Called when new object is spawned to the level.
	//		eventObject: yam2d::GameObject* = object which was spawn.
	// - ObjectDeleted:
	//		Called when object is deleted from the level.
	//		eventObject: yam2d::GameObject* = object which is going to be deleted.
	// - ItemPicked: 
	//		Called when item has beed picked by game object.
	//		eventObject: ItemPickedEvent* = Item picked event
	// - ItemDropped: 
	//		Called when item has beed dropped by game object.
	//		eventObject: yam2d::GameObject* = object which was dropped  (Dynamite).
	virtual void onGameEvent(GameEnvironmentInfoProvider* environmentInfo, const std::string& eventName, yam2d::Object* eventObject)
	{
		if (eventName == "ObjectSpawned" || eventName == "ObjectDeleted")
		{
			yam2d::GameObject* gameObject = dynamic_cast<yam2d::GameObject*>(eventObject);
			assert(gameObject != 0);
			// Don't print spawned weapon projectiles or explosions.
			if (gameObject->getType() != "Missile"
				&& gameObject->getType() != "Bullet"
				&& gameObject->getType() != "Grenade"
				&& gameObject->getType() != "Mine"
				&& gameObject->getType() != "SmallExplosion"
				&& gameObject->getType() != "MediumExplosion"
				&& gameObject->getType() != "BigExplosion"
				&& gameObject->getType() != "MineExplosion"
				&& gameObject->getType() != "GrenadeExplosion")
			{
				// Prints: Soldier, Robot, HomeBase, Flag
				if (gameObject->getProperties().hasProperty("teamIndex"))
				{
					int teamName = gameObject->getProperties()["teamIndex"].get<int>();
					yam2d::esLogMessage("%s: gameObjectType=%s, teamName=%d", eventName.c_str(), gameObject->getType().c_str(), teamName);
				}
				else
				{
					yam2d::esLogMessage("%s: gameObjectType=%s", eventName.c_str(), gameObject->getType().c_str());
				}
			}
		}
		else if (eventName == "ItemPicked")
		{
			ItemEvent* itemEvent = dynamic_cast<ItemEvent*>(eventObject);
			assert(itemEvent != 0);
			int teamIndex = itemEvent->getObject()->getGameObject()->getProperties()["teamIndex"].get<int>();

			yam2d::esLogMessage("%s: gameObjectType=%s, team=%d", eventName.c_str(), itemEvent->getItemGameObject()->getType().c_str(), teamIndex);

			for (size_t i = 0; i < m_autoAttackFlagCarryingBots.size(); ++i)
			{
				m_autoAttackFlagCarryingBots[i]->setTargetToShoot(itemEvent->getObject()->getGameObject(), 1.9f, 0.05f);
			}

			if (teamIndex == getMyTeamIndex())
			{
				// My team picked item. 
				// Go to enemy home base.
				const yam2d::GameObject* homeBase = environmentInfo->getEnemyHomeBase(this);
				for (size_t i = 0; i < m_directMoverAIControllers.size(); ++i)
				{
					m_directMoverAIControllers[i]->setMoveTargetObject(homeBase, 1.0f);
				}

				for (size_t i = 0; i < m_MyAIControllers.size(); ++i)
				{
					m_MyAIControllers[i]->setMoveTargetObject(homeBase, 1.0f);
					m_MyAIControllers[i]->setNewPath();
				}
			}
			else
			{
				// Other team picked the item.
				// Go to enemy's enemy == me home base.
				const yam2d::GameObject* homeBase = environmentInfo->getMyHomeBase(this);
				for (size_t i = 0; i < m_directMoverAIControllers.size(); ++i)
				{
					m_directMoverAIControllers[i]->setMoveTargetObject(homeBase, 1.0f);
				}
				for (size_t i = 0; i < m_MyAIControllers.size(); ++i)
				{
					m_MyAIControllers[i]->setMoveTargetObject(homeBase, 1.0f);
					m_MyAIControllers[i]->setNewPath();
				}

				for (size_t i = 0; i < m_MyAIControllers.size(); ++i)
				{
					m_MyAIControllers[i]->setTargetToShoot(itemEvent->getObject()->getGameObject(), 1.1f, 0.05f);
					m_MyAIControllers[i]->setNewPath();
				}
			}
		}
		else if (eventName == "ItemDropped")
		{
			ItemEvent* itemEvent = dynamic_cast<ItemEvent*>(eventObject);
			assert(itemEvent != 0);
			yam2d::esLogMessage("%s: gameObjectType=%s", eventName.c_str(), itemEvent->getItemGameObject()->getType().c_str());
			
			for (size_t i = 0; i < m_autoAttackFlagCarryingBots.size(); ++i)
			{
				m_autoAttackFlagCarryingBots[i]->resetTargetToShoot();
			}

			for (size_t i = 0; i < m_MyAIControllers.size(); ++i)
			{
				m_MyAIControllers[i]->resetTargetToShoot();
			}

			// Item propped.
			// Start going straight to dynamite
			const yam2d::GameObject* dynamite = environmentInfo->getDynamite();
			for (size_t i = 0; i < m_directMoverAIControllers.size(); ++i)
			{
				m_directMoverAIControllers[i]->setMoveTargetObject(dynamite, 1.0f);
			}

			for (size_t i = 0; i < m_MyAIControllers.size(); ++i)
			{
				m_MyAIControllers[i]->setMoveTargetObject(dynamite, 1.0f);
				m_MyAIControllers[i]->setNewPath();
			}
		}
		else
		{
			assert(0); // Should be impossible, because unknown message id.
		}
	}

	// Send, when game object receives an event.
	// Event name tells the event in question, each event type may have eventObject data associated with the event.
	//
	// Currently supported eventNames and eventObject data desctiption:
	// - Collision: 
	//		Called when game object collides to another object. 
	//		eventObject: CollisionEvent* = Information about collision.
	// - TakingDamage:
	//		Called when game object is taking damage.
	//		eventObject: yam2d::GameObject* = object which give damage to the object. Typically this is bullet, missile, mine or grenade etc.
	// - ZeroHealth: 
	//		Called when game object is going to die, because of zero health.
	//		eventObject: 0 always.
	virtual void onGameObjectEvent(GameEnvironmentInfoProvider* environmentInfo, yam2d::GameObject* gameObject, const std::string& eventName, yam2d::Object* eventObject)
	{
		if (eventName == "Collision")
		{
			CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*>(eventObject);
			assert(collisionEvent != 0);
			yam2d::GameObject* otherGo = collisionEvent->getOtherGameObject();
			std::string otherType = otherGo->getType();
			yam2d::vec2 localNormal = collisionEvent->getLocalNormal();
	//		yam2d::esLogMessage("%s %s: myBody=%s toObject=%s bodyType=%s, localNormal=<%.2f,%.2f> ", gameObject->getType().c_str(), eventName.c_str(), collisionEvent->getMyBody()->getType().c_str(),
	//			otherType.c_str(),
	//			collisionEvent->getOtherBody()->getType().c_str(), localNormal.x, localNormal.y);
		}
		else if (eventName == "TakingDamage")
		{
			int teamIndex = gameObject->getProperties()["teamIndex"].get<int>();

			TakingDamageEvent* damageEvent = dynamic_cast<TakingDamageEvent*>(eventObject);			
			yam2d::GameObject* damageFromObject = damageEvent->getFromObject();
			float newHealth = damageEvent->getNewHealth();
			yam2d::esLogMessage("%s(team=%d) %s: fromObject=%s. New health: %3.1f", gameObject->getType().c_str(), teamIndex, eventName.c_str(), damageFromObject->getType().c_str(), newHealth);
		}
		else if (eventName == "ZeroHealth")
		{
			int teamIndex = gameObject->getProperties()["teamIndex"].get<int>();
			yam2d::esLogMessage("%s(team=%d) %s.", gameObject->getType().c_str(), teamIndex, eventName.c_str());
		}
		else
		{
			assert(0); // Should be impossible, because unknown message id.
		}
	}
};


int main(int argc, char *argv[])
{
	GameApp app(argc, argv, 1280, 800);
	//app.disableLayer("Ground");
	app.disableLayer("ObjectSpawns");
	app.disableLayer("GroundTypeColliders");
//	app.disableLayer("GroundMoveSpeed");
	app.setLayerOpacity("GroundMoveSpeed", 0.7f);
	app.setDefaultGame("level0.tmx", "PTAI", "PTAI", 4);
//	app.setDefaultGame("Level0.tmx", "AutoAttackFlagCarryingBot", "DirectMoverAI", 4);
//	app.setDefaultGame("Level0.tmx", "DirectMoverAI", "AutoAttackFlagCarryingBot", 4);
//	app.setDefaultGame("Level0.tmx", "DirectMoverAI", "AutoAttackFlagCarryingBot", 4);
	MyPlayerController player1Controller;
	app.setPlayer1Controller(&player1Controller);
	MyPlayerController player2Controller;
	app.setPlayer2Controller(&player2Controller);

	return app.run();
}
