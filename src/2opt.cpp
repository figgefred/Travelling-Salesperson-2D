#include "2opt.h"
#include <vector>
#include "map.h"
#include <iostream>
#include <ctime>

using namespace std;

TwoOpt::TwoOpt(Map* map) {
	this->map = map;	
}

// From wikipedia psuedocode:
// http://en.wikipedia.org/wiki/2-opt
tour* TwoOpt::swap(tour* t, int from, int to)
{	
	int toswap = (to - from) / 2 + (to - from) % 2; 
	//~ cout << "Before swap of " << from << " " << to << " " << toswap << endl;
	//~ printTour(t);
	// 1. take route[0] to route[i-1] and add them in order to new_route
	// 2. take route[i] to route[k] and add them in reverse order to new_route
	// 3. take route[k+1] to end and add them in order to new_route
	for(int i = 0; i < toswap; ++i) {		
		int left = from+i;
		int right = to-i;				
		//~ cout << i << ": Swap: p[" << left << "]: " << t->path[left] << " and p[" << right << "]: " << t->path[right] << endl;
		int tmp = t->path[left];		
		t->path[left] = t->path[right];
		t->path[right] = tmp;
	}
		
	//~ cout << "After swap" << endl;
	//~ printTour(t);
	
	return t;	
}


double TwoOpt::getNewCost(tour* t, int i1, int i2) {
	int e1 = t->path[i1];
	int s2 = t->path[i2];
	
	int lastIndex = t->path.size()-1;	
	//~ int s1 = t->path[i1-1];
	int s1 = i1 > 0 ? t->path[i1-1] : t->path[lastIndex];	
	int e2 = i2 < lastIndex ? t->path[i2+1] : t->path[0];
	
 
	double cost = 0;	
	cost -= map->getDistance(e1, s1);		
	cost -= map->getDistance(s2, e2);		
	cost += map->getDistance(e1, e2);	
	cost += map->getDistance(s2, s1);	
	
	return cost;
	
	
	//~ int lastIndex = t->path.size()-1;	
	//~ int e1 = t->path[i1];
	
	//~ int s2 = t->path[i2];
	//~ int e2 = i2 < lastIndex ? t->path[i2+1] : t->path[0];

	//~ double cost = 0;		
	//~ cost -= map->getDistance(s1, e1);		
	//~ cost -= map->getDistance(s2, e2);	
	//~ 
	//~ cost += map->getDistance(e1, e2);	
	//~ cost += map->getDistance(s2, s1);
	
	//~ return cost;
}

bool TwoOpt::findNewTour(tour* t, std::clock_t start) {		
	double bestcost = 0;
	int besti = -1;
	int bestj = -1;
	unsigned int size = t->path.size();
	for(unsigned int i = 1; i < size && start + 1.5*CLOCKS_PER_SEC > std::clock(); ++i)
	{
		//~ int city = t->path[i];
		//~ double maxdistallowed = map->getDistance(i,i);				
		
		for(unsigned int j = i+1; j < size; ++j)
		{				
			double cost = getNewCost(t, i, j);
			
			if(cost < bestcost) {									
				bestcost = cost;
				besti = i;
				bestj = j;	
			}		
		}	
	}	

	if(besti < 0)
		return false;

	//~ cout << "Best cost: " << bestcost << " " << besti << " " << bestj << endl;	
	t = swap(t, besti, bestj);
	t->cost += bestcost;
	
	
	return true;
}

tour* TwoOpt::getBetterTour(tour* t)
{	
	std::clock_t start = std::clock();   
	
	int i = 0;
	t->cost = map->getTourDistance(t);		
	bool timedout = false;
	while(findNewTour(t, start) && !timedout){
		timedout = (( std::clock() - start ) / (double) CLOCKS_PER_SEC) > 1.5;
		//~ cout << t->cost << endl;
		i++;
	}
	
	//~ cout << "Attempts: " << i << " " << ((timedout) ? "true" : "false") << endl;
	
	return t;	
}


