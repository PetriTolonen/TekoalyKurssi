#include "ClosedList.h"

ClosedList::ClosedList()
{

}

ClosedList::~ClosedList()
{

}

void ClosedList::addToClosedList(SearchNode* node)
{
	closedList[node->pos] = node;
}

bool ClosedList::isInClosedList(const Position& pos)
{
	return closedList.find(pos) != closedList.end();
}

void ClosedList::clear()
{
	closedList.clear();
}