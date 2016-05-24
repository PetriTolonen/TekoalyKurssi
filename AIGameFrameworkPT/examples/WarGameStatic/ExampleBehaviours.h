// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef EXAMPLE_BEHAVIOURS_H_
#define EXAMPLE_BEHAVIOURS_H_

#include "GameEvents.h"
#include "PlayerController.h"

// DirectMoverAI provides following functionality:
//
// * Try move directly to position:
//    void setMoveTargetObject(const yam2d::GameObject* gameObjectToGo, float reachTolerance);
// * Stops moving:
//    void resetMoveTargetObject();
// * Returns distance to given move destination:
//    float getDistanceToDestination() const
//
class DirectMoverAI : public CharacterController
{
public:
	DirectMoverAI(yam2d::GameObject* owner, GameController* gameController, BotType botType)
		: CharacterController(owner, gameController, botType)
		, m_gameObjectToGo(0)
		, m_reachTolerance(0.0f)
		, m_distanceToDestination(0.0f)
		, m_collisionToHomeBase(false)
	{
	}

	virtual ~DirectMoverAI(void)
	{
	}

	virtual void onMessage(const std::string& msgName, yam2d::Object* eventObject)
	{
		// Call base class onMessage
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

	// This virtual method is automatically called byt map/layer, when update is called from main.cpp
	virtual void update(float deltaTime)
	{
		// Call update to base class
		CharacterController::update(deltaTime);
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

	float getDistanceToDestination() const
	{
		return m_distanceToDestination;
	}

private:
	const yam2d::GameObject* m_gameObjectToGo;
	float m_reachTolerance;
	float m_distanceToDestination;
	bool m_collisionToHomeBase;
};

// AutoAttackFlagCarryingBot provides following functionality:
//
// * Starts aiming and shooting to target. Aiming is done, until aimTolerance is reached. predictionDistance is used as to forecast factor for speed prediction:
//    void setTargetToShoot(const yam2d::GameObject* gameObjectToShoot, float predictionDistance, float aimTolerance);
// * Stops automatic shooting:
//    void resetTargetToShoot();
//
class AutoAttackFlagCarryingBot : public CharacterController
{
public:
	AutoAttackFlagCarryingBot(yam2d::GameObject* owner, GameController* gameController, BotType botType)
		: CharacterController(owner, gameController, botType)
		, m_gameObjectToShoot(0)
		, m_predictionDistance(0.0f)
		, m_aimTolerance(0.0f)
	{
	}

	virtual ~AutoAttackFlagCarryingBot(void)
	{
	}

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
		if (m_gameObjectToShoot != 0)
		{
			float rotation = m_gameObjectToShoot->getRotation();
			slm::vec2 enemyForwardDir;
			enemyForwardDir.x = cosf(rotation);
			enemyForwardDir.y = sinf(rotation);
			autoUsePrimaryWeapon(m_gameObjectToShoot->getPosition() + m_predictionDistance*enemyForwardDir, m_aimTolerance);
		}
	}

private:
	const yam2d::GameObject* m_gameObjectToShoot;
	float m_predictionDistance;
	float m_aimTolerance;
};


#endif

