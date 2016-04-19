#pragma once

#include "SearchNode.h"
#include <vector>
#include <Texture.h>
#include <StreamTexture.h>

namespace
{
	void setPathColor(yam2d::StreamTexture* t, int x, int y)
	{
		t->getPixel(x, y)[0] = 0xff;
		t->getPixel(x, y)[1] = 0x00;
		t->getPixel(x, y)[2] = 0xff;
	}

	bool isWhite(unsigned char* p)
	{
		return p[1] < 100;
	}
}

class SearchLevel
{
public:
	SearchLevel(yam2d::Texture* input);
	~SearchLevel();

	float GetG(SearchNode* fromNode, const Position& toPos);
	float GetH(const Position& fromPos, const Position& toPos);

	bool isWalkable(int x, int y);

	std::vector<Position> getAdjacentNodes(int posX, int posY);
private:
	yam2d::Texture* inputTexture;	
};