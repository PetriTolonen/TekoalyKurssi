// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef GAME_CONFIG_H_
#define GAME_CONFIG_H_

// Home Base config
static const float HOME_BASE_SIZE = 2.0f;
//static const float HOME_BASE_TRIGGER_SIZE = 2.0f;

// Dynamite -item config
static const float DYNAMITE_SIZE = 1.5f;
static const float DYNAMITE_TRIGGER_SIZE = 1.5f;


// Soldier bullets has 50 damage/second
static const float BULLET_COOLDOWN_TIME = 0.1f;
static const float BULLET_SPEED = 15.0f;
static const float BULLET_MAX_DAMAGE = 5.0f;
static const float BULLET_SIZE = 0.3f;


// Robot missiles has 50 damage/second
static const float MISSILE_COOLDOWN_TIME = 1.0f;
static const float MISSILE_SPEED = 15.0f;
static const float MISSILE_MAX_DAMAGE = 50.0f;
static const float MISSILE_SIZE = 0.5f;

// Grenade damage 30
static const float GRENADE_COOLDOWN_TIME = 3.0f;
static const float GRENADE_EXPLOSION_DELAY = 2.0f;
static const float GRENADE_SPEED = 7.0f;
static const float GRENADE_MAX_DAMAGE = 30.0f;
static const float GRENADE_SIZE = 0.5f;
static const float GRENADE_DAMAGE_SPHERE_SIZE = 5.0f;


// Mine damage 30
static const float MINE_COOLDOWN_TIME = 1.0f;
static const float MINE_ARMING_TIME = 1.0f;
static const float MINE_MAX_DAMAGE = 30.0f;
static const float MINE_SIZE = 0.5f;
static const float MINE_DAMAGE_SPHERE_SIZE = 5.0f;

static const float SOLDIER_SIZE = 1.0f;
static const float SOLDIER_MAX_LINEAR_SPEED = 2.0f;
static const float SOLDIER_MAX_ANGULAR_SPEED = 2.0f;

static const float ROBOT_SIZE = 1.0f;
static const float ROBOT_MAX_LINEAR_SPEED = 1.5f;
static const float ROBOT_MAX_ANGULAR_SPEED = 1.0f;

#endif


