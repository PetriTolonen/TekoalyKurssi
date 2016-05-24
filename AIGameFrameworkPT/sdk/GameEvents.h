// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef GAME_EVENTS_H_
#define GAME_EVENTS_H_ 

// Include base class
#include <Object.h>
#include <GameObject.h>


class PhysicsBody;
class b2Body;
class CharacterController;
class PickableItemController;

class YAM2D_API CollisionEvent : public yam2d::Object
{
public:
	YAM2D_API CollisionEvent(yam2d::GameObject* goA, yam2d::GameObject* goB);
//CollisionEvent(b2Body* bA, b2Body* bB, const yam2d::vec2& localNormal = yam2d::vec2(0.0f));
	YAM2D_API CollisionEvent(PhysicsBody* goA, PhysicsBody* goB, const yam2d::vec2& localNormal = yam2d::vec2(0.0f));

	YAM2D_API virtual ~CollisionEvent();

	YAM2D_API bool isValid() const;

	//PhysicsBody* getMyBody() const { return m_myBody; }
	//PhysicsBody* getOtherBody() const { return m_otherBody; }
	YAM2D_API yam2d::GameObject* getMyGameObject() const;
	YAM2D_API yam2d::GameObject* getOtherGameObject() const;

	YAM2D_API const yam2d::vec2& getLocalNormal() const { return m_localNormal; }
	//b2Body* getBodyA() const { return m_bA; }
	//b2Body* getBodyB() const { return m_bB; }
	YAM2D_API bool isCollisionToSelf() const;
private:
	PhysicsBody* m_myBody;
	PhysicsBody* m_otherBody;
	yam2d::vec2 m_localNormal;
	yam2d::GameObject* m_goA;
	yam2d::GameObject* m_goB;
};


class YAM2D_API TakingDamageEvent : public yam2d::Object
{
public:
	YAM2D_API TakingDamageEvent(yam2d::GameObject* fromObject, float damageAmount, float newHealth);

	YAM2D_API virtual ~TakingDamageEvent();

	YAM2D_API yam2d::GameObject* getFromObject() const { return m_fromObject; }
	YAM2D_API float getDamageAmount() const { return m_damageAmount; }
	YAM2D_API float getNewHealth() const { return m_newHealth; }
private:
	yam2d::GameObject* m_fromObject;
	float m_damageAmount;
	float m_newHealth;
};

class YAM2D_API ItemEvent : public yam2d::Object
{
public:
	YAM2D_API ItemEvent(CharacterController* object, PickableItemController* item);

	YAM2D_API virtual ~ItemEvent();

	YAM2D_API yam2d::GameObject* getCharacterGameObject() const;
	YAM2D_API yam2d::GameObject* getItemGameObject() const;

	// Which character controller picked the item.
	YAM2D_API CharacterController* getCharacterController() const { return m_object; }
	YAM2D_API PickableItemController* getItem() const { return m_item; }
private:
	CharacterController* m_object;
	PickableItemController* m_item;
};


#endif