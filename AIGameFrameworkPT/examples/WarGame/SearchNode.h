#pragma once
#include <algorithm>
typedef std::pair<int, int> Position;

class SearchNode
{
public:
	SearchNode(const Position& curPos, float h, float deltaG, SearchNode* prev);
	~SearchNode();
	void resetPrev(SearchNode* prev, float deltaG);
	float getDistance() const;
	static bool lessThan(SearchNode* n1, SearchNode* n2);

	SearchNode* prevNode;
	float G;
	float H;
	float F;

	Position pos;
};