// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef MY_GAME_BASE_CONTROLLER_H_
#define MY_GAME_BASE_CONTROLLER_H_ 

// Include base class
#include <GameObject.h>

class GameController;


// Use yam2d::Component as base class for our player. Use also yam2d::Updatable -interface, for update-method.
class YAM2D_API GameBaseController : public yam2d::Component, public yam2d::Updatable
{
public:
	YAM2D_API GameBaseController(yam2d::GameObject* owner, GameController* gameController);
	YAM2D_API virtual ~GameBaseController(void);
		
	YAM2D_API yam2d::GameObject* getGameObject() { return (yam2d::GameObject*)getOwner(); }
	YAM2D_API const yam2d::GameObject* getGameObject() const { return (const yam2d::GameObject*)getOwner(); }

	//  Used by game internally.
	YAM2D_API GameController* getGameController() { return m_gameController; }
	YAM2D_API const GameController* getGameController() const { return m_gameController; }

	// Returns rotated forward direction (i.e. direction, where the gun is pointing)
	YAM2D_API slm::vec2 getForwardDirection() const;
		
	YAM2D_API void sendMessage(const std::string& msgName, yam2d::Object* obj);

protected:
	YAM2D_API virtual void onMessage(const std::string& msgName, yam2d::Object* obj)
	{
	}
	
private:
	GameController* m_gameController;
};



#endif


