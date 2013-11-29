
#ifndef _TABUSEARCH
#include "localsearch.h"
#include "types.h"
#include <vector>

class TabuSearch : public LocalSearch
{
	private:
		std::vector<int*> tabulist;
		void swap(int city1, int city2, tour*);

	public:
		TabuSearch(Map*, std::vector<coordinate*>);
		virtual ~TabuSearch();
		virtual tour* getBetterTour(tour*);
		virtual void reset();
};

#define _TABUSEARCH
#endif