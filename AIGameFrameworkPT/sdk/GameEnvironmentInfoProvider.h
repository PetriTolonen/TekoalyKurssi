// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef GAME_ENVIRONMENT_INFO_PROVIDER_H_
#define GAME_ENVIRONMENT_INFO_PROVIDER_H_ 

#include <GameObject.h>
#include <stdint.h>
#include "AIMapLayer.h"
/*
*/

class PlayerController;

class GameEnvironmentInfoProvider
{
protected:
	GameEnvironmentInfoProvider()
	{
	}

	virtual ~GameEnvironmentInfoProvider()
	{
	}

public:
	virtual const yam2d::GameObject* getDynamite() const = 0;
	virtual const yam2d::GameObject* getEnemyHomeBase(PlayerController* player) const = 0;
	virtual const yam2d::GameObject* getMyHomeBase(PlayerController* player) const = 0;

	virtual AIMapLayer* getAILayer(const std::string layerName) = 0;

};







#endif


