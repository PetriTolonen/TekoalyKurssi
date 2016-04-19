#include "SearchNode.h"

SearchNode::SearchNode(const Position& curPos, float h, float deltaG, SearchNode* prev) : prevNode(0), pos(curPos), G(0), H(h)
{
	resetPrev(prev, deltaG);
}

SearchNode::~SearchNode()
{

}

void SearchNode::resetPrev(SearchNode* prev, float deltaG)
{
	prevNode = prev;
	if (prev == 0)
	{
		G = 0.0f;
	}
	else
	{
		G = deltaG + prev->G;
	}
	F = H + G;
}

float SearchNode::getDistance() const
{
	return F;
}

bool SearchNode::lessThan(SearchNode* n1, SearchNode* n2)
{
	return n1->getDistance() > n2->getDistance();
}