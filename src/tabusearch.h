
#ifndef _TABUSEARCH
#include "localsearch.h"
#include "types.h"
#include <vector>
#include <unordered_set>

class TabuSearch : public LocalSearch
{
	private:
		std::unordered_set<int> tabulist;
		void swap(std::vector<int>*, int city1, int city2);
		double getNewCost(std::vector<int>*, int, int);
		tour* findNewTour(tour*);

	public:
		TabuSearch(Map*);
		virtual ~TabuSearch();
		virtual tour* getBetterTour(tour*);
		virtual void reset();
};

#define _TABUSEARCH
#endif