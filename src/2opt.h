#ifndef _2OPT
#define _2OPT
#include "localsearch.h"
#include "types.h"
#include "map.h"
#include <ctime>

class TwoOpt : public LocalSearch
{	
	
	private: 
		//~ tour* swap(tour* t, tour* newTour, int from, int to);
		inline void swap(tour* t, int from, int to);
		// what is the cost if we were to swap?
		inline double getNewCost(tour* t, int from, int to);
		bool findNewTour(tour* t, std::clock_t start);
	public:
		TwoOpt(Map* map);
		virtual tour* getBetterTour(tour*);

};


#endif
