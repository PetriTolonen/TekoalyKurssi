#include "PTAI.h"

namespace PetriTolonen
{
	PetriTolonenController::PetriTolonenController(yam2d::GameObject* owner, GameController* gameController, BotType botType)
		: CharacterController(owner, gameController, botType)
		, m_gameObjectToGo(0)
		, m_reachTolerance(0.0f)
		, m_distanceToDestination(0.0f)
		, m_collisionToHomeBase(false)
		, m_gameObjectToShoot(0)
		, m_predictionDistance(0.0f)
		, m_aimTolerance(0.0f)
		//, debugLayer(nullptr)
		, moveSpeedLayer(nullptr)
		, indexOfCurrentWaypoint(0)
		, stuckTimer(0)
		, imStuck(false)
		, stuckRandX(0)
		, stuckRandY(0)
		, moving(false)
	{
		myPathFinder = new PathFindingApp();
	}

	void PetriTolonenController::updateCurrentWaypoint()
	{
		if (myPathFinder->getWaypoints().size() > 0)
		{
			float reachTolerance = 0.55f;

			if (abs(myPathFinder->getWaypoints()[indexOfCurrentWaypoint].x - getGameObject()->getPosition().x) < reachTolerance &&  abs(myPathFinder->getWaypoints()[indexOfCurrentWaypoint].y - getGameObject()->getPosition().y) < reachTolerance)
			{
				if (indexOfCurrentWaypoint > 0)
				{
					indexOfCurrentWaypoint--;
				}
			}
		}
	}

	void PetriTolonenController::setNewPath()
	{
		if (m_gameObjectToGo != nullptr)
		{
			myPathFinder->getWaypoints().clear();
			myPathFinder->update(getGameObject()->getPosition(), m_gameObjectToGo->getPosition());
			indexOfCurrentWaypoint = myPathFinder->getWaypoints().size() - 2;
		}
	}

	PetriTolonenController::~PetriTolonenController(void)
	{
	}

	void PetriTolonenController::onMessage(const std::string& msgName, yam2d::Object* eventObject)
	{
		// Call onMessage to base class
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

	void PetriTolonenController::setMoveTargetObject(const yam2d::GameObject* gameObjectToGo, float reachTolerance)
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

	void PetriTolonenController::resetMoveTargetObject()
	{
		m_gameObjectToGo = 0;
		m_reachTolerance = 0.0f;
		m_distanceToDestination = 0.0f;
		stop();
	}

	void PetriTolonenController::setTargetToShoot(const yam2d::GameObject* gameObjectToShoot, float predictionDistance, float aimTolerance)
	{
		m_gameObjectToShoot = gameObjectToShoot;
		m_predictionDistance = predictionDistance;
		m_aimTolerance = aimTolerance;
	}

	void PetriTolonenController::resetTargetToShoot()
	{
		m_gameObjectToShoot = 0;
		m_predictionDistance = 0.0f;
		m_aimTolerance = 0.0f;
	}

	// This virtual method is automatically called by map/layer, when update is called from main.cpp
	void PetriTolonenController::update(float deltaTime)
	{
		//uint8_t RED_PIXEL[4] = { 0xff, 0x00, 0x00, 0x50 };
		//
		//for (int i = 0; i < myPathFinder->getWaypoints().size(); ++i)
		//{
		//	size_t posX = myPathFinder->getWaypoints()[i].x;
		//	size_t posY = myPathFinder->getWaypoints()[i].y;
		//	if (debugLayer != nullptr)
		//	{
		//		// debug draw testi
		//		debugLayer->setPixel(posX, posY, RED_PIXEL);
		//	}
		//}

		// Call update to base class
		CharacterController::update(deltaTime);

		if (m_gameObjectToGo != 0)
		{
			// Move to position
			if (indexOfCurrentWaypoint > 0 && moving == true)
			{
				if (indexOfCurrentWaypoint < 2)
				{
					m_distanceToDestination = moveDirectToPosition(m_gameObjectToGo->getPosition(), m_reachTolerance);
				}
				else if (!imStuck)
				{
					m_distanceToDestination = moveDirectToPosition(slm::vec2(myPathFinder->getWaypoints()[indexOfCurrentWaypoint].x - 0.5f, myPathFinder->getWaypoints()[indexOfCurrentWaypoint].y), m_reachTolerance);
				}
				else
				{
					m_distanceToDestination = moveDirectToPosition(slm::vec2(stuckRandX, stuckRandY), m_reachTolerance);
				}
			}
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

		if (m_gameObjectToShoot != 0)
		{
			float rotation = m_gameObjectToShoot->getRotation();
			slm::vec2 enemyForwardDir;
			enemyForwardDir.x = cosf(rotation);
			enemyForwardDir.y = sinf(rotation);
			autoUsePrimaryWeapon(m_gameObjectToShoot->getPosition() + m_predictionDistance*enemyForwardDir, m_aimTolerance);
		}

		if (moving)
		{
			stuckCheck();
		}

		updateCurrentWaypoint();
	}

	void PetriTolonenController::stuckCheck()
	{
		if (stuckTimer == 0)
		{
			oldPos = getGameObject()->getPosition();
		}
		stuckTimer++;

		if (stuckTimer > 500)
		{
			slm::vec2 currentPos = getGameObject()->getPosition();
			if (abs(oldPos.x - currentPos.x) < 0.1f && abs(oldPos.y - currentPos.y) < 0.1f)
			{
				imStuck = true;
				srand(time(NULL));
				stuckRandX = rand() % 6 + 0;
				stuckRandY = rand() % 6 + 0;

				stuckRandX = oldPos.x + stuckRandX - 3;
				stuckRandY = oldPos.y + stuckRandY - 3;

				if (indexOfCurrentWaypoint < myPathFinder->getWaypoints().size())
				{
					indexOfCurrentWaypoint++;
				}
			}
			else
			{
				imStuck = false;
			}
			stuckTimer = 0;
		}
	}

	float PetriTolonenController::getDistanceToDestination() const
	{
		return m_distanceToDestination;
	}

	//void PetriTolonenController::setDebugLayer(AIMapLayer* layer)
	//{
	//	this->debugLayer = layer;
	//}

	void PetriTolonenController::setMoveSpeedLayer(AIMapLayer* layer)
	{
		this->moveSpeedLayer = layer;

		myPathFinder->setMoveLayer(moveSpeedLayer);
	}

	void PetriTolonenController::startMoving()
	{
		moving = true;
	}
};