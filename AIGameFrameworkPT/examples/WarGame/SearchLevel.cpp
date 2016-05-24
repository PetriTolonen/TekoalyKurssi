#include "SearchLevel.h"

SearchLevel::SearchLevel(AIMapLayer* input) : inputLayer(input)
{

}

SearchLevel::~SearchLevel()
{

}

float SearchLevel::GetG(SearchNode* fromNode, const Position& toPos)
{
	float dX = (float)(toPos.first - fromNode->pos.first);
	float dY = (float)(toPos.second - fromNode->pos.second);
	float result = sqrtf(dX*dX + dY*dY);
	return result;
}
float SearchLevel::GetH(const Position& fromPos, const Position& toPos)
{
	float dX = (float)(toPos.first - fromPos.first);
	float dY = (float)(toPos.second - fromPos.second);
	float result = sqrtf(dX*dX + dY*dY);
	return result;
}

bool SearchLevel::isWalkable(int posX, int posY)
{
	if (posX < 0 || posY < 0 || posX >= inputLayer->getWidth() || posY >= inputLayer->getHeight())
	{
		return false;
	}
	unsigned char* pixel = inputLayer->getPixel(posX, posY);
	bool isNotWalkable = isGreen(pixel);
	return !isNotWalkable;
}

std::vector<Position> SearchLevel::getAdjacentNodes(int posX, int posY)
{
	std::vector<Position> result;
	int pass = 0;

	if (isWalkable(posX + 1, posY) && isWalkable(posX + 2, posY))
	{
		result.push_back(Position(posX + 1, posY));
		pass++;
	}
	if (isWalkable(posX - 1, posY) && isWalkable(posX - 2, posY))
	{
		result.push_back(Position(posX - 1, posY));
		pass++;
	}
	if (isWalkable(posX, posY + 1) && isWalkable(posX, posY + 2))
	{
		result.push_back(Position(posX, posY + 1));
		pass++;
	}
	if (isWalkable(posX, posY - 1) && isWalkable(posX, posY - 2))
	{
		result.push_back(Position(posX, posY - 1));
		pass++;
	}
	if (pass >= 3)
	{
		return result;
	}
	else
	{
		result.clear();
		return result;
	}	
}