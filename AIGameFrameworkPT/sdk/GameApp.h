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
#include <yam2d_dll_api.h>

#define APP_VERSION "0.3"

class GameApp;

/**
 * Game State interface. Use this as a base class for application state. 
 * Subclasses will make specialized implementation for update and render -methods.
 */
class YAM2D_API GameState : public yam2d::Object
{
public:
	YAM2D_API virtual ~GameState();

protected:
	/// Class constructor.
	YAM2D_API GameState(GameApp* app);

	/// Returns the GameApp there the state is belonging.
	YAM2D_API GameApp* getApp();


public:
	// Update method must be implemented in inherited class. 
	YAM2D_API virtual bool update(yam2d::ESContext* ctx, float deltaTime) = 0;

	// Redner method must be implemented in inherited class. 
	YAM2D_API virtual void render(yam2d::ESContext *ctx) = 0;
	
	YAM2D_API virtual bool showMinimized() const = 0;

private:
	GameApp* m_app;
};


class PlayerController;

/**
 * Class for game application.
 */
class YAM2D_API GameApp : public yam2d::Object
{
public:

	/// Default constructor will initialize application without the state. Set state after creation using setState -method.
	YAM2D_API GameApp(int argc, char *argv[], int screenWidth, int screenHeight);

	YAM2D_API virtual ~GameApp();

	// Disable drawing layers if needed.
	YAM2D_API void disableLayer(const char* const layerName);

	YAM2D_API void setLayerOpacity(const char* const layerName, float val);


	YAM2D_API void setPlayer1Controller(PlayerController* playerController);
	YAM2D_API PlayerController* getPlayer1Controller();
	YAM2D_API void setPlayer2Controller(PlayerController* playerController);
	YAM2D_API PlayerController* getPlayer2Controller();

	YAM2D_API void setDefaultGame(
		const char* const levelFileName, 
		const char* const team1ControllerComponentNameOrDllPrefixName, 
		const char* const team2ControllerComponentNameOrDllPrefixName,
		const char* const localTeamNameInNetGame,
		int numBotsPerTeam,
		const char* const defaultHostName = 0);

	YAM2D_API int run();

	/// Sets the new state of the application.
	YAM2D_API void setState(GameState* newState);

	// Initialize the game
	YAM2D_API static bool initApp(yam2d::ESContext *ctx);

	// Deinitialize the game
	YAM2D_API static void deinitApp(yam2d::ESContext *ctx);

	// Update game
	YAM2D_API static void updateApp(yam2d::ESContext* ctx, float deltaTime);

	// Draw game
	YAM2D_API static void drawApp(yam2d::ESContext *ctx);

	YAM2D_API void setLevelFileName(const std::string&);

	YAM2D_API const std::string& getLocalTeamName() const;
	YAM2D_API const std::string& getLevelFileName() const;
	YAM2D_API const std::string& getTeam1ControllerComponentName() const;
	YAM2D_API const std::string& getTeam2ControllerComponentName() const;



	YAM2D_API void setPlayerName(int index, const std::string name) {
		m_playerNames[index] = name;
	}

	YAM2D_API std::string getHostName() const;

	YAM2D_API int getDefaultNumBotsPerTeam() const { return m_defaultNumBotsPerTeam; }
	YAM2D_API const std::vector<std::string>& getDisabledLayers() const { return m_disabledLayers; }
	YAM2D_API const std::vector<std::string>& getOpacityLayers() const { return m_opacityLayers; }
	YAM2D_API const std::vector<float>& getOpacityValues() const { return m_opacityValues; }

	YAM2D_API yam2d::PropertySet& getCmdArgs() { return m_cmdArgs; }
	YAM2D_API const yam2d::PropertySet& getCmdArgs() const { return m_cmdArgs; }



private:
	std::string getTeam1ControllerComponentNameDll() const;
	std::string getTeam2ControllerComponentNameDll() const;

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

	std::string m_playerNames[2];

	std::string m_defaultHostName;
	std::string m_localTeamNameInNetGame;
	std::vector<std::string> m_disabledLayers;
	std::vector<std::string> m_opacityLayers;
	std::vector<float> m_opacityValues;
	int m_defaultNumBotsPerTeam;
	int m_screenWidth;
	int m_screenHeight;
	yam2d::PropertySet m_cmdArgs;
};






#endif //_GAME_APP_H_