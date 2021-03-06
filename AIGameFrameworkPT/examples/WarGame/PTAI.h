#include "ExampleBehaviours.h"
#include "JoystickController.h"
#include "PathFindingApp.h"
#include "slm/vec2.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "GameObject.h"

namespace PTAInamespace
{
	class PTAI : public CharacterController
	{
	public:
		PTAI(yam2d::GameObject* owner, GameController* gameController, BotType botType);

		void updateCurrentWaypoint();

		void setNewPath();

		virtual ~PTAI(void);

		virtual void onMessage(const std::string& msgName, yam2d::Object* eventObject);

		void setMoveTargetObject(const yam2d::GameObject* gameObjectToGo, float reachTolerance);

		void resetMoveTargetObject();

		void setTargetToShoot(const yam2d::GameObject* gameObjectToShoot, float predictionDistance, float aimTolerance);

		void resetTargetToShoot();

		// This virtual method is automatically called by map/layer, when update is called from main.cpp
		virtual void update(float deltaTime);

		void stuckCheck();

		float getDistanceToDestination() const;

		void setDebugLayer(AIMapLayer* layer);

		void setMoveSpeedLayer(AIMapLayer* layer);

		void addEnemy(yam2d::GameObject* enemy);

		void addFriendly(yam2d::GameObject* friendly);

		void startMoving();

	private:
		const yam2d::GameObject* m_gameObjectToGo;
		float m_reachTolerance;
		float m_distanceToDestination;
		bool m_collisionToHomeBase;

		const yam2d::GameObject* m_gameObjectToShoot;
		float m_predictionDistance;
		float m_aimTolerance;

		AIMapLayer* debugLayer;
		AIMapLayer* moveSpeedLayer;

		yam2d::Ref<PTAInamespace::PathFindingApp> myPathFinder;

		int indexOfCurrentWaypoint;
		int stuckTimer;
		slm::vec2 oldPos;
		bool imStuck;

		int stuckRandX;
		int	stuckRandY;

		bool moving;
	};
};