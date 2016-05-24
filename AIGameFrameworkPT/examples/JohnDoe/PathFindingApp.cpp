#include "PathFindingApp.h"
#include <Input.h>
#include <ElapsedTimer.h>
#include <StreamTexture.h>
#include <Text.h>

#include "OpenList.h"
#include "ClosedList.h"
#include "SearchLevel.h"
#include "SearchNode.h"

namespace JohnDoe
{
	//namespace
	//{
	//	void setPathColor(yam2d::StreamTexture* t, int x, int y)
	//	{
	//		t->getPixel(x, y)[0] = 0xff;
	//		t->getPixel(x, y)[1] = 0x00;
	//		t->getPixel(x, y)[2] = 0xff;
	//	}
	//
	//	bool isRed(unsigned char* p)
	//	{
	//		return p[0] > 200;
	//	}
	//
	//	bool isGreen(unsigned char* p)
	//	{
	//		return p[1] > 200;
	//	}
	//
	//	bool isBlue(unsigned char* p)
	//	{
	//		return p[2] > 200;
	//	}
	//}

	PathFindingApp::PathFindingApp()
		: m_batch()
	{
		m_batch = new yam2d::SpriteBatchGroup();

		m_searchCompleted = false;
		m_searchTimer = 0.0f;

	}



	PathFindingApp::~PathFindingApp()
	{
	}


	void PathFindingApp::setMoveLayer(AIMapLayer* mapLayer)
	{
		this->mapLayer = mapLayer;
	}

	bool PathFindingApp::update(slm::vec2 AIpos, slm::vec2 targetPos)
	{
		// Find start and end
		int startX, startY, endX, endY;
		startX = startY = endX = endY = -1;

		startX = AIpos.x;
		startY = AIpos.y;

		endX = targetPos.x;
		endY = targetPos.y;

		// Update path find!! Set m_searchCompleted to true, when path found, so the texture data is updated.
		if (startX >= 0 && startY >= 0 && endX >= 0 && endY >= 0)
		{
			m_searchCompleted = doPathfinding(startX, startY, endX, endY);
		}
		else
		{
			return false;
		}

		return true;
	}

	bool PathFindingApp::doPathfinding(int startX, int startY, int endX, int endY)
	{
		bool done = true;
		OpenList openList;
		ClosedList closedList;
		SearchLevel searchlevel(mapLayer);
		SearchNode* result = 0;

		Position startPosition = Position(startX, startY);
		Position endPosition = Position(endX, endY);
		SearchNode* newNode = new SearchNode(startPosition, searchlevel.GetH(startPosition, endPosition), 0, 0);
		openList.insertToOpenList(newNode);

		while (!openList.isEmpty())
		{
			SearchNode* prev = openList.removeSmallestFFromOpenList();
			if (prev->pos == endPosition)
			{
				result = prev; break;
			}
			else
			{
				closedList.addToClosedList(prev);

				std::vector<Position> adjacentNodes = searchlevel.getAdjacentNodes(prev->pos.first, prev->pos.second);
				for (size_t i = 0; i < adjacentNodes.size(); i++)
				{
					if (closedList.isInClosedList(adjacentNodes[i]))
					{
						continue;
					}

					SearchNode* n = openList.findFromOpenList(adjacentNodes[i]);
					if (n == 0)
					{
						SearchNode* newNode = new SearchNode(adjacentNodes[i],
							searchlevel.GetH(adjacentNodes[i], endPosition),
							searchlevel.GetG(prev, adjacentNodes[i]), prev);
						openList.insertToOpenList(newNode);
					}
					else
					{
						SearchNode* newNode = new SearchNode(adjacentNodes[i],
							searchlevel.GetH(adjacentNodes[i], endPosition),
							searchlevel.GetG(prev, adjacentNodes[i]), prev);
						if (n->getDistance() < newNode->getDistance())
						{
							n->resetPrev(newNode->prevNode, searchlevel.GetG(newNode->prevNode, n->pos));
						}
					}
				}
			}
		}

		if (result == 0)
		{
			printf("No can do");
			return true;
		}

		while (result != 0)
		{
			wayPoints.push_back(slm::vec2(result->pos.first, result->pos.second));
			result = result->prevNode;
		}

		return true;
	}

	std::vector<slm::vec2> PathFindingApp::getWaypoints()
	{
		return wayPoints;
	}
};
