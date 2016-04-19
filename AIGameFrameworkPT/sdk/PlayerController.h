// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef PLAYER_CONTROLLER_H_
#define PLAYER_CONTROLLER_H_ 

// Include base class
#include "GameEnvironmentInfoProvider.h"
#include "CharacterController.h"



class PlayerController
{
private:
	int m_teamIndex;

public:
	PlayerController()
		: m_teamIndex(-1)
	{
	}

	virtual ~PlayerController()
	{
	}

	void setMyTeamIndex(int teamIndex)
	{
		m_teamIndex = teamIndex;
	}
	
	int getMyTeamIndex() const
	{
		return m_teamIndex;
	}

	// Called, when bots are spawn. Shall return correct player character controller for bot if given name.
	virtual CharacterController* createPlayerCharacterController(GameController* gameController, yam2d::GameObject* ownerGameObject, const std::string& playerName, BotType type) = 0;
	
	// Called, when bots have spawn. Can be used some custom initialization after spawn.
	virtual void onGameStarted(GameEnvironmentInfoProvider* environmentInfo) = 0;

	// Called when game has ended. Can be used some cuystom deinitialization after game.
	virtual void onGameOver(GameEnvironmentInfoProvider* environmentInfo, const std::string& gameResultString) = 0;

	// Called each frame. Update you player character controllers in this function.
	virtual void onUpdate(GameEnvironmentInfoProvider* environmentInfo, float deltaTime) = 0;

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
	//		eventObject: ItemDropperdEvent* = Item dropped event
	virtual void onGameEvent(GameEnvironmentInfoProvider* environmentInfo, const std::string& eventName, yam2d::Object* eventObject) = 0;
	
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
	virtual void onGameObjectEvent(GameEnvironmentInfoProvider* environmentInfo, yam2d::GameObject* gameObject, const std::string& eventName, yam2d::Object* eventObject) = 0;

};







#endif


