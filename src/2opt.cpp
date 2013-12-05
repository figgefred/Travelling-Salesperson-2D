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
/*
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
*/

//swaps two cities
void TwoOpt::swap(tour* t, int i1, int i2)
{
	int left1 = i1-1;
	int right1 = i1+1;
	int left2 = i2-1;
	int right2 = i2+1;

	int lastIndex = t->path.size()-1;

	// First remove old costs.
//	cout << "Cost is " << t->cost << endl;

	if(i1 == lastIndex)
		right1 = 0;
	else if( i2 == lastIndex)	
		right2 = 0;
	
	double cost = 0;
	cost -= map->getDistance(t->path[left1], t->path[i1]);	
	cost -= map->getDistance(t->path[right1], t->path[i1]);
	cost -= map->getDistance(t->path[left2], t->path[i2]);
	cost -= map->getDistance(t->path[right2], t->path[i2]);

//	cout << "Cost after reduce is " << t->cost << endl;
	// Do switch
	int tmp = t->path[i1];
	t->path[i1] = t->path[i2];
	t->path[i2] = tmp;
	
	cost += map->getDistance(t->path[left1], t->path[i1]);
	cost += map->getDistance(t->path[right1], t->path[i1]);
	cost += map->getDistance(t->path[left2], t->path[i2]);
	cost += map->getDistance(t->path[right2], t->path[i2]);
	
	t->cost += cost;
}

double TwoOpt::getNewCost(tour* t, int i1, int i2) {
	int city1 = t->path[i1];
	int city2 = t->path[i2];
	
	int lastIndex = t->path.size()-1;	
	//~ cout << lastIndex << endl;
	int left1 = t->path[i1-1];
	int right1 = i1 < lastIndex ? t->path[i1+1] : t->path[0];
	int left2 = t->path[i2-1];
	int right2 = i2 < lastIndex ? t->path[i2+1] : t->path[0];
	

	double cost = 0;	
	
	cost -= map->getDistance(city1, left1);		
	cost -= map->getDistance(city2, right2);	
	cost += map->getDistance(city2, left1);	
	cost += map->getDistance(city1, right2);
	
	if(right1 == city2) {
		//~ cout << i1 << " " << i2 << endl;
		return cost;
	}
	
	cost -= map->getDistance(city1, right1);
	cost -= map->getDistance(city2, left2);	
	cost += map->getDistance(city1, left2);
	cost += map->getDistance(city2, right1);
	
	return cost;
}


bool TwoOpt::findNewTour(tour* t) {	
	//~ double oldcost = t->cost;
	double bestcost = 0;
	int besti = -1;
	int bestj = -1;
	for(unsigned int i = 1; i < t->path.size(); ++i)
	{
		for(unsigned int j = i+1; j < t->path.size(); ++j)
		{
			double cost = getNewCost(t, i, j);
			
			if(cost < bestcost) {									
				bestcost = cost;
				besti = i;
				bestj = j;
				//~ cout << i << " " << j << endl;
			}		
		}	
	}	

	if(besti < 0)
		return false;	
		
	int tmp = t->path[bestj];
	t->path[bestj] = t->path[besti];
	t->path[besti] = tmp;	
	t->cost += bestcost;
	//~ cout << besti << " -> " << bestj << endl;
	
	return true;
}

tour* TwoOpt::getBetterTour(tour* t)
{	
	int i = 0;
	t->cost = map->getTourDistance(t);	
	while(findNewTour(t)){
		cout << t->cost << endl;
		i++;
	}
		
	
	
	//~ cout << "Attempts: " << i << endl;
	
	return t;	
}


