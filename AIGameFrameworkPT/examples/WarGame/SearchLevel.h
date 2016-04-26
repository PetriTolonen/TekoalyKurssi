#pragma once

#include "SearchNode.h"
#include <vector>
#include <Texture.h>
#include <StreamTexture.h>
#include "slm/vec2.h"
#include <AIMapLayer.h>

namespace
{
	void setPathColor(AIMapLayer* t, int x, int y)
	{
		t->getPixel(x, y)[0] = 0xff;
		t->getPixel(x, y)[1] = 0x00;
		t->getPixel(x, y)[2] = 0xff;
	}

	bool isRed(unsigned char* p)
	{
		return p[0] > 200;
	}

	bool isGreen(unsigned char* p)
	{
		if (p[1] == 0)
		{
			return true;
		}
		return false;
	}

	bool isBlue(unsigned char* p)
	{
		return p[2] > 200;
	}
}

class SearchLevel
{
public:
	SearchLevel(AIMapLayer* input);
	~SearchLevel();

	float GetG(SearchNode* fromNode, const Position& toPos);
	float GetH(const Position& fromPos, const Position& toPos);

	bool isWalkable(int x, int y);

	std::vector<Position> getAdjacentNodes(int posX, int posY);
private:
	AIMapLayer* inputLayer;	
};