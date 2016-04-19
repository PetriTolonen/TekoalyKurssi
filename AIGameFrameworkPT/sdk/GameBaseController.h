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
class GameBaseController : public yam2d::Component, public yam2d::Updatable
{
public:
	GameBaseController(yam2d::GameObject* owner, GameController* gameController);
	virtual ~GameBaseController(void);
		
	yam2d::GameObject* getGameObject() { return (yam2d::GameObject*)getOwner(); }
	const yam2d::GameObject* getGameObject() const { return (const yam2d::GameObject*)getOwner(); }

	//  Used by game internally.
	GameController* getGameController() { return m_gameController; }
	const GameController* getGameController() const { return m_gameController; }

	// Returns rotated forward direction (i.e. direction, where the gun is pointing)
	slm::vec2 getForwardDirection() const;
		
	void sendMessage(const std::string& msgName, yam2d::Object* obj);

protected:
	virtual void onMessage(const std::string& msgName, yam2d::Object* obj)
	{
	}
	
private:
	GameController* m_gameController;
};



#endif


