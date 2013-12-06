
#ifndef _TABUSEARCH
#include "localsearch.h"
#include "types.h"
#include <vector>
#include <unordered_set>
#include <list>

class TabuSearch : public LocalSearch
{
	private:
		std::unordered_set<int> tabu_list;
		std::list<int> tabu_order;
		void swap(std::vector<int>*, int, int);
		tour* flip(tour*, int, int );
		double getNewCost(tour*, int, int);
		tour* findNewTour(tour*);
		bool isTabu(int);
		void tabu_move(int);
		void expire_move();

	public:
		TabuSearch(Map*);
		virtual ~TabuSearch();
		virtual tour* getBetterTour(tour*);
		virtual void reset();
};

#define _TABUSEARCH
#endif