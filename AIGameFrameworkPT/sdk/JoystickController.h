// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef JOYSTICK_CONTROLLER_H_
#define JOYSTICK_CONTROLLER_H_ 

// Include base class
#include "CharacterController.h"


class XBOXController;


class JoystickController : public CharacterController
{
public:
	JoystickController(yam2d::GameObject* owner, GameController* gameController, BotType botType, int controllerIndex);
	virtual ~JoystickController(void);

	// This virtual method is automatically called byt map/layer, when update is called from main.cpp
	virtual void update(float deltaTime);

private:
	yam2d::Ref<XBOXController> m_joystick;
};





#endif


