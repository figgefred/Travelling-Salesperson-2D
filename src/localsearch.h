
#ifndef _LOCALSEARCH
#include "map.h"
#include "types.h"
#include <vector>
#include <ctime>

class LocalSearch
{
	protected:
		Map* map;
	public:
		virtual ~LocalSearch(){};
		virtual tour* getBetterTour(tour*, std::clock_t) = 0;
};

#define _LOCALSEARCH
#endif
