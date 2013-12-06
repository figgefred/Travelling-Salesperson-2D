
#ifndef _TABUSEARCH
#include "localsearch.h"
#include "types.h"
#include <vector>
#include <unordered_set>
#include <list>
#include <ctime>

class TabuSearch : public LocalSearch
{
	private:
		std::unordered_set<int> tabu_list;
		std::list<int> tabu_order;
		
		tour* flip(tour*, int, int );
		tour* swap(tour* t, int from, int to, double cost);
		double getNewCost(tour*, int, int);
		bool findNewTour(tour*);
		
		inline bool isTabu(int);
		void tabu_move(int);
		void expire_move();

	public:
		TabuSearch(Map*);
		virtual ~TabuSearch();
		virtual tour* getBetterTour(tour*, std::clock_t);
};

#define _TABUSEARCH
#endif
