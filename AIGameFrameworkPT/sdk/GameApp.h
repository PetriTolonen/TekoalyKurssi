// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _GAME_APP_H_
#define _GAME_APP_H_
#include <Object.h>
#include <Ref.h>
#include <es_util.h>
#include <PropertySet.h>

class GameApp;

/**
 * Game State interface. Use this as a base class for application state. 
 * Subclasses will make specialized implementation for update and render -methods.
 */
class GameState : public yam2d::Object
{
public:
	virtual ~GameState();

protected:
	/// Class constructor.
	GameState(GameApp* app);

	/// Returns the GameApp there the state is belonging.
	GameApp* getApp();

public:
	// Update method must be implemented in inherited class. 
	virtual bool update(yam2d::ESContext* ctx, float deltaTime) = 0;

	// Redner method must be implemented in inherited class. 
	virtual void render(yam2d::ESContext *ctx) = 0;

private:
	GameApp* m_app;
};


class PlayerController;

/**
 * Class for game application.
 */
class GameApp : public yam2d::Object
{
public:

	/// Default constructor will initialize application without the state. Set state after creation using setState -method.
	GameApp(int argc, char *argv[], int screenWidth, int screenHeight);

	virtual ~GameApp();

	// Disable drawing layers if needed.
	void disableLayer(const char* const layerName);

	void setLayerOpacity(const char* const layerName, float val);

	void setPlayer1Controller(PlayerController* playerController) { m_player1Controller = playerController; }
	PlayerController* getPlayer1Controller() { return m_player1Controller; }
	void setPlayer2Controller(PlayerController* playerController) { m_player2Controller = playerController; }
	PlayerController* getPlayer2Controller() { return m_player2Controller; }

	void setDefaultGame(
		const char* const levelFileName, 
		const char* const team1ControllerComponentName, 
		const char* const team2ControllerComponentName,
		int numBotsPerTeam);

	int run();

	/// Sets the new state of the application.
	void setState(GameState* newState);

	// Initialize the game
	static bool initApp(yam2d::ESContext *ctx);

	// Deinitialize the game
	static void deinitApp(yam2d::ESContext *ctx);

	// Update game
	static void updateApp(yam2d::ESContext* ctx, float deltaTime);

	// Draw game
	static void drawApp(yam2d::ESContext *ctx);

	const std::string& getLevelFileName() const;
	const std::string& getTeam1ControllerComponentName() const;
	const std::string& getTeam2ControllerComponentName() const;


	int getDefaultNumBotsPerTeam() const { return m_defaultNumBotsPerTeam; }
	const std::vector<std::string>& getDisabledLayers() const { return m_disabledLayers; }
	const std::vector<std::string>& getOpacityLayers() const { return m_opacityLayers; }
	const std::vector<float>& getOpacityValues() const { return m_opacityValues; }

	const yam2d::PropertySet& getCmdArgs() const { return m_cmdArgs; }
private:

	/// Updates the current state.
	bool update(yam2d::ESContext* ctx, float deltaTime);

	/// Renders the current state.
	void render(yam2d::ESContext *ctx);


	static GameApp* instance;
	yam2d::Ref<GameState> m_currentState;
	yam2d::ESContext esContext;
	PlayerController* m_player1Controller;
	PlayerController* m_player2Controller;
	std::string m_defaultLevelFileName;
	std::string m_defaultTeam1ControllerComponentName;
	std::string m_defaultTeam2ControllerComponentName;
	std::vector<std::string> m_disabledLayers;
	std::vector<std::string> m_opacityLayers;
	std::vector<float> m_opacityValues;
	int m_defaultNumBotsPerTeam;

	yam2d::PropertySet m_cmdArgs;
};






#endif //_GAME_APP_H_