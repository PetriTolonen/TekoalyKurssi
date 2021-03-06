#pragma once
#include "SearchNode.h"
#include <vector>
namespace PTAInamespace
{
	class OpenList
	{
	public:
		OpenList();
		~OpenList();

		SearchNode* findFromOpenList(const Position& pos);
		void insertToOpenList(SearchNode* n);
		void sortOpenList();
		SearchNode* removeSmallestFFromOpenList();

		bool isEmpty();
		void clear();
	private:
		typedef std::vector<SearchNode*> OpenListType;
		OpenListType openList;
	};
};