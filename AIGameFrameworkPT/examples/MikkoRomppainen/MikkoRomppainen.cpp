#include "CharacterController.h"
#include "PlayerController.h"
namespace MikkoRomppainen
{
	class MikkoRomppainenController : public CharacterController
	{
	public:
		MikkoRomppainenController(yam2d::GameObject* owner, GameController* gameController, BotType botType)
			: CharacterController(owner, gameController, botType)
		{
		}

		virtual ~MikkoRomppainenController(void)
		{
		}

		virtual void onMessage(const std::string& msgName, yam2d::Object* eventObject)
		{
			// Call onMessage to base class
			CharacterController::onMessage(msgName, eventObject);
			// TODO: handle message...
		}

		// This virtual method is automatically called byt map/layer, when update is called from main.cpp
		virtual void update(float deltaTime)
		{
			// Call update to base class
			CharacterController::update(deltaTime);
			// TODO: Update...
		}

	private:

	};

	class MikkoRomppainenPlayer : public PlayerController
	{
	private:
		std::string m_myTeamName;
		std::vector< yam2d::Ref<MikkoRomppainenController> > m_myAIControllers;
	public:
		MikkoRomppainenPlayer()
			: PlayerController()
		{
		}

		virtual ~MikkoRomppainenPlayer()
		{
		}

		virtual void setMyTeamName(std::string& teamName)
		{
			m_myTeamName = teamName;
		}

		virtual CharacterController* createPlayerCharacterController(GameController* gameController, yam2d::GameObject* ownerGameObject, const std::string& playerName, BotType type)
		{
			if (playerName == "MikkoRomppainenController")
			{
				MikkoRomppainenController* myAI = new MikkoRomppainenController(ownerGameObject, gameController, type);
				m_myAIControllers.push_back(myAI);
				return myAI;
			}

			return 0;
		}

		virtual void onGameStarted(GameEnvironmentInfoProvider* environmentInfo)
		{
		}

		virtual void onGameOver(GameEnvironmentInfoProvider* environmentInfo, const std::string& gameResultString)
		{
		}

		virtual void onUpdate(GameEnvironmentInfoProvider* environmentInfo, float deltaTime)
		{
		}

		virtual void onGameEvent(GameEnvironmentInfoProvider* environmentInfo, const std::string& eventName, yam2d::Object* eventObject)
		{
		}

		virtual void onGameObjectEvent(GameEnvironmentInfoProvider* environmentInfo, yam2d::GameObject* gameObject, const std::string& eventName, yam2d::Object* eventObject)
		{
		}
	};


	PlayerController* createNewPlayer()
	{
		return new MikkoRomppainenPlayer();
	}
}



