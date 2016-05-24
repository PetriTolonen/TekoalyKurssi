#include "CharacterController.h"
#include "PlayerController.h"
namespace JohnDoe
{
	class JohnDoeController : public CharacterController
	{
	public:
		JohnDoeController(yam2d::GameObject* owner, GameController* gameController, BotType botType)
			: CharacterController(owner, gameController, botType)
		{
		}

		virtual ~JohnDoeController(void)
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

	class JohnDoePlayer : public PlayerController
	{
	private:
		std::string m_myTeamName;
		std::vector< yam2d::Ref<JohnDoeController> > m_myAIControllers;
	public:
		JohnDoePlayer()
			: PlayerController()
		{
		}

		virtual ~JohnDoePlayer()
		{
		}

		virtual void setMyTeamName(std::string& teamName)
		{
			m_myTeamName = teamName;
		}

		virtual CharacterController* createPlayerCharacterController(GameController* gameController, yam2d::GameObject* ownerGameObject, const std::string& playerName, BotType type)
		{
			if (playerName == "JohnDoe")
			{
				JohnDoeController* myAI = new JohnDoeController(ownerGameObject, gameController, type);
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
			yam2d::esLogMessage("onGameOver: %s wins!", gameResultString.c_str());

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
		return new JohnDoePlayer();
	}
}



