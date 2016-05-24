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


class YAM2D_API JoystickController : public CharacterController
{
public:
	YAM2D_API JoystickController(yam2d::GameObject* owner, GameController* gameController, BotType botType, int controllerIndex);
	YAM2D_API virtual ~JoystickController(void);

	// This virtual method is automatically called byt map/layer, when update is called from main.cpp
	YAM2D_API virtual void update(float deltaTime);

private:
	yam2d::Ref<XBOXController> m_joystick;
};





#endif


