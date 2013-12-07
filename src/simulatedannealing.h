#ifndef _simulatedannealing
#define _simulatedannealing
#include "localsearch.h"
#include "types.h"
#include "2opt.h"
#include <vector>
#include <unordered_set>
#include <list>
#include <ctime>

class SimulatedAnnealing  : public TwoOpt
{
	protected:
		tour* findLeastBadTour(tour*, std::clock_t);
		tour* randomBadModify(tour*);
		tour* cloneTour(tour*);
	
	public:
		SimulatedAnnealing(Map* map);
		virtual tour* getBetterTour(tour*, std::clock_t);
	
};


#endif
