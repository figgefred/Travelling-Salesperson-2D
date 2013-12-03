#ifndef _2OPT
#define _2OPT
#include "localsearch.h"
#include "types.h"
#include "map.h"

class TwoOpt : public LocalSearch
{	
	
	private: 
		tour* swap(tour* t, int from, int to);
		tour* findNewTour(tour* t);
	public:
		TwoOpt(Map* map);
		virtual tour* getBetterTour(tour*);

};


#endif
