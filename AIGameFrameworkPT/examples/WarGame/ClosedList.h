#pragma once

#include "SearchNode.h"
#include <map>

class ClosedList
{
public:
	ClosedList();
	~ClosedList();

	void addToClosedList(SearchNode* node);
	bool isInClosedList(const Position& pos);
	void clear();

private:
	typedef std::map<Position, SearchNode*> ClosedListType;
	ClosedListType closedList;
};