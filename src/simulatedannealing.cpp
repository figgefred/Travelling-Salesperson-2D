#include "simulatedannealing.h"
#include <stdlib.h> // rand
#include <vector>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(Map* map) : TwoOpt(map) {
	this->map = map;
}

tour* SimulatedAnnealing::cloneTour(tour* original) {
	tour* newTour = new tour();
	newTour->path = original->path;
	newTour->cost = original->cost;
	return newTour;
}

tour* SimulatedAnnealing::getBetterTour(tour* t, std::clock_t deadline) {
	
	tour* best_so_far = NULL;
	t->cost = map->getTourDistance(t);
	
	
	while(std::clock() < deadline) {	
			
		//~ cout << t->cost << endl;
		//~ cout << "derp1" << endl;
		while(findNewTour(t, deadline)) {
			// Keep improving until done!
		}
		//~ cout << t->cost << endl;
		if(std::clock() > deadline)
			break;
		
		if(best_so_far == NULL || best_so_far->cost > t->cost)
			best_so_far = cloneTour(t);
			
		//~ cout << "derp3" << endl;	
		//~ t = findLeastBadTour(t, deadline);
		t = randomBadModify(t);
		//~ cout << t->cost << endl;	
	}
	
	//~ cout << best_so_far->cost << endl;
	//~ cout << "Broke out!" << endl;
	return best_so_far;
}

tour* SimulatedAnnealing::randomBadModify(tour* t) {
	//~ tour* t = cloneTour(original);
	int dim = map->getDimension();
	
	int i1 = rand() % dim;
	int i2 = rand() % dim;
	
	int tmp = t->path[i1];
	t->path[i1] = t->path[i2];
	t->path[i2] = tmp;
	t->cost = map->getTourDistance(t);
	return t;	
}

tour* SimulatedAnnealing::findLeastBadTour(tour* t, std::clock_t deadline) {
	//~ tour* t = cloneTour(original);
	double bestcost = -1;
	int besti = -1;
	int bestj = -1;
	unsigned int size = t->path.size();
	for(unsigned int i = 1; i < size && std::clock() < deadline; ++i)
	{			
		//~ int city = t->path[i];
		//~ double maxAllowedDist = map->getDistance(city,city);
		
		for(unsigned int j = i+1; j < size; ++j)
		{				
			//~ if(maxAllowedDist < map->getDistance(city,t->path[j]))
				//~ continue;
						
			double cost = getNewCost(t, i, j);
			
			if(cost > 0) {									
				bestcost = cost;
				besti = i;
				bestj = j;	
				cout << i << " " << j << " " << bestcost << endl;
			}		
		}	
	}	
	
	if(besti > -1)
		swap(t, besti, bestj, bestcost);	
	return t;
}
