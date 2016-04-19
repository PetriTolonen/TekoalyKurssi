// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef CHARACTER_CONTROLLER_H_
#define CHARACTER_CONTROLLER_H_ 

// Include base class
#include "GameBaseController.h"
class PickableItemController;

enum BotType
{
	SOLDIER,
	ROBOT
};

// Use yam2d::Component as base class for our player. Use also yam2d::Updatable -interface, for update-method.
class CharacterController : public GameBaseController
{
public:
	CharacterController(yam2d::GameObject* owner, GameController* gameController, BotType botType);
	virtual ~CharacterController(void);

	virtual void onMessage(const std::string& msgName, yam2d::Object* obj);

	// This virtual method is automatically called byt map/layer, when update is called from main.cpp
	virtual void update( float deltaTime );


	// Returns sin of angle between vectors. Can be used to detect that is aiming angle reached. Smaller absolute value means that target has been aimed more.
	// After calling this CharacterController automatically tries to adjust aiming next update to correct direction.
	float aimToDirection(const slm::vec2& toDirection);

	// Start walking to given direction.
	void moveToDirection(const slm::vec2& toDirection);

	// Stops walking to given direction.
	void stop();

	// Tries to shoot to object direction, if gun has cooled down.
	bool tryUsePrimaryWeapon();

	// Tries to shoot to object direction, if gun has cooled down.
	bool tryUseSecondaryWeapon();
	bool tryDropMine(const slm::vec2& dir);
	bool tryThrowGrenade(const slm::vec2& dir);

	// Has primary weapon cooled down.
	bool hasCooledDownPrimary();

	// Has secondary weapon cooled down.
	bool hasCooledDownSecondary();

	// Enables autoshoot behaviour (to position).
	// This must be called each frame, or else the auto shooting is not updated (shooting is stopped). During autoshoot enabled, the object can not move or aim.
	// toPosition is position where to shoot.
	// aimTol is tolerance value for shooting accuracy. Smaller value means that object is needed to be aimed more accurately, than when using bigger aimTol value.
	void autoUsePrimaryWeapon(const slm::vec2& toPosition, float aimTol);

	// Enables auto move to position.
	// toPosition is position where to move.
	// This must be called each frame, or else the auto move is not updated (bot is stopped).
	// moveTol is tolerance value for mooving end accuracy. Smaller value means that object is trying to move even closer to toPosition than bigger value. Small values may cause weird behaviour with big sime steps.
	float moveDirectToPosition(const slm::vec2& toPosition, float moveTol);
		
	// Returns true, if bomb is picked by this object.
	bool hasItem();

	// Drops flag
	void dropItem1();

	// Set object automatically to pick flag, if it is dropped. 
	void preferPickItem();

	// Returns true if this character is soldier
	bool isSoldier();

	// Returns true if this character is robot
	bool isRobot();

private:

	float m_timeSinceLastPrimary;
	float m_timeSinceLastSecondary;
	slm::vec2 m_direction;
	float m_maxLinearSpeed;
	PickableItemController* m_pickedFlag;
	PickableItemController* m_perferPickFlag;
	bool m_pickFlagIfCollides;
	BotType m_botType;

};




#endif


