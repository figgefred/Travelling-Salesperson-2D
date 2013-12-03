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
tour* TwoOpt::swap(tour* t, tour* newTour, int from, int to)
{	
	newTour->path.clear();
	//  1. take route[0] to route[i-1] and add them in order to new_rout
	for(int i = 0; i < from; ++i) {
		newTour->path.push_back(t->path[i]);		
	}
	// 2. take route[i] to route[k] and add them in reverse order to new_route
	for(int i = to; i >= from; --i) {		
		newTour->path.push_back(t->path[i]);
	}
	// 3. take route[k+1] to end and add them in order to new_route
	for(unsigned int i = to+1; i < t->path.size(); ++i) {		
		newTour->path.push_back(t->path[i]);
	}
	
	//~ cout << t->path.size() << endl;
	//~ cout << from << " " << to << endl;
	//~ cout << newTour->path.size() << endl;
	
	//~ cout << "Swap finished. " << newTour->path.size() << endl;
	newTour->cost = map->getTourDistance(newTour);
	return newTour;	
}

tour* TwoOpt::findNewTour(tour* t, tour* newTour) {
	//~ cout << t->cost << " " << newTour->cost << endl;
	for(unsigned int i = 1; i < t->path.size(); ++i)
	{
		for(unsigned int j = i+1; j < t->path.size(); ++j)
		{
			newTour = swap(t, newTour, i, j);
						
			if(newTour->cost < t->cost)
				return newTour;							
		}		
		//~ cout << i << endl; 
	}	
	return NULL;	
}

tour* TwoOpt::getBetterTour(tour* t)
{	
	tour* newTour = new tour(0);
	for(int i = 0; i < 10; i++) {
		//~ double best = map->getTourDistance(t);
		newTour = findNewTour(t, newTour);
		
		if(newTour == NULL)		
			break;
		
		cout << t << " " << newTour << " " << t->cost << " " << newTour->cost << " " << newTour->path.size() << endl;
			
		t->path.clear();
		for(unsigned int i = 0; i < newTour->path.size(); i++) {
			t->path.push_back(newTour->path[i]);
			t->cost = newTour->cost;
		}	
					
	}
	
	return t;	
}


