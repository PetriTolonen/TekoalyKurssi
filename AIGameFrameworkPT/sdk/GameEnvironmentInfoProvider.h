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
#include <yam2d_dll_api.h>
/*
*/

class PlayerController;

class YAM2D_API GameEnvironmentInfoProvider
{
protected:
	YAM2D_API GameEnvironmentInfoProvider()
	{
	}

	YAM2D_API virtual ~GameEnvironmentInfoProvider()
	{
	}

public:
	YAM2D_API virtual const yam2d::GameObject* getDynamite() const = 0;
	YAM2D_API virtual std::vector<const yam2d::GameObject*> getEnemyBots(PlayerController* player) const = 0;
	YAM2D_API virtual std::vector<const yam2d::GameObject*> getMyBots(PlayerController* player) const = 0;
	YAM2D_API virtual const yam2d::GameObject* getEnemyHomeBase(PlayerController* player) const = 0;
	YAM2D_API virtual const yam2d::GameObject* getMyHomeBase(PlayerController* player) const = 0;
	YAM2D_API virtual AIMapLayer* getAILayer(const std::string layerName) = 0;

};







#endif


