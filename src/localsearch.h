
#ifndef _LOCALSEARCH
#include "map.h"
#include "types.h"
#include <vector>

class LocalSearch
{
	protected:
		Map* map;
	public:
		virtual ~LocalSearch(){};
		virtual tour* getBetterTour(tour*) = 0;
		//~ virtual void reset() = 0;
};

#define _LOCALSEARCH
#endif
