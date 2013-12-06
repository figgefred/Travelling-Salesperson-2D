#ifndef _2OPT
#define _2OPT
#include "localsearch.h"
#include "types.h"
#include "map.h"
#include <ctime>

class TwoOpt : public LocalSearch
{	
	private: 
		const static bool findBest = true;
		
		
		void swap(tour* t, int from, int to, double cost);
		// what is the cost if we were to swap?
		inline double getNewCost(tour* t, int from, int to);
		bool findBestNewTour(tour* t, std::clock_t start);
		bool findNewTour(tour* t, std::clock_t start);
	public:
		TwoOpt(Map* map);
		virtual tour* getBetterTour(tour*, std::clock_t);

};


#endif
