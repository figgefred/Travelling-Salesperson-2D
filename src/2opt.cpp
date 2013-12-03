#include "2opt.h"
#include <vector>
#include "map.h"
#include <iostream>

using namespace std;

TwoOpt::TwoOpt(Map* map) {
	this->map = map;	
}

// From wikipedia psuedocode:
// http://en.wikipedia.org/wiki/2-opt
tour* TwoOpt::swap(tour* t, int from, int to)
{
	tour* newTour = new tour(0);
	//  1. take route[0] to route[i-1] and add them in order to new_rout
	for(int i = 0; i < from; ++i) {
		newTour->path.push_back(t->path[i]);
		//~ cout << t->path[i] << endl;
	}
	// 2. take route[i] to route[k] and add them in reverse order to new_route
	for(int i = to; i >= from; --i) {
		//~ cout << t->path[i] << endl;
		newTour->path.push_back(t->path[i]);
	}
	// 3. take route[k+1] to end and add them in order to new_route
	for(int i = to+1; i < t->path.size(); ++i) {
		//~ cout << t->path[i] << endl;
		newTour->path.push_back(t->path[i]);
	}
	
	//~ cout << t->path.size() << endl;
	//~ cout << from << " " << to << endl;
	//~ cout << newTour->path.size() << endl;
	
	//~ cout << "Swap finished. " << newTour->path.size() << endl;
	newTour->cost = map->getTourDistance(newTour);
	return newTour;	
}

tour* TwoOpt::findNewTour(tour* t) {
	tour* bestPossibleNewRoute = NULL;
	for(int i = 1; i < t->path.size(); ++i)
	{
		for(int j = i+1; j < t->path.size(); ++j)
		{
			tour* newPossibleRoute = swap(t, i, j);
						
			if(newPossibleRoute->cost < t->cost && (bestPossibleNewRoute == NULL || newPossibleRoute->cost < bestPossibleNewRoute->cost)) {
				bestPossibleNewRoute = newPossibleRoute;
			} else {
				// memory leak?
				delete newPossibleRoute;	
			}
			
		}		 
	}	
	
	return bestPossibleNewRoute;	
}

tour* TwoOpt::getBetterTour(tour* t)
{
	while(true) {
		//~ double best = map->getTourDistance(t);
		tour* newTour = findNewTour(t);
		
		if(newTour == NULL)		
			break;
			
		delete t;
		t = newTour;		
		cout << t->cost << endl;
	}
	
	return t;	
}


