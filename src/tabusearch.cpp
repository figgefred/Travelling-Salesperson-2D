
//#include <math.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <unordered_set>
#include <list>

#include "types.h"
#include "map.h"
#include "tabusearch.h"

#include <ctime>

using namespace std;

TabuSearch::TabuSearch(Map* m)
{
	map = m;
}

TabuSearch::~TabuSearch()
{

}

// Private
void TabuSearch::tabu_move(int candidate)
{
	tabu_list.insert(candidate);
	tabu_order.push_back(candidate);
}

bool TabuSearch::isTabu(int city)
{
	return tabu_list.find(city) != tabu_list.end();
}

void TabuSearch::expire_move()
{
	int cand = tabu_order.front();
	tabu_list.erase(cand);
	tabu_order.pop_front();
}

// http://en.wikipedia.org/wiki/2-opt
// 1. take route[0] to route[i-1] and add them in order to new_route
// 2. take route[i] to route[k] and add them in reverse order to new_route
// 3. take route[k+1] to end and add them in order to new_route
tour* TabuSearch::flip(tour* curr_tour, int i, int k)
{
	int count = curr_tour->path.size();
	int kPlus = k+1;
	vector<int> newRoute(count, count);
	int index;
	int j = 0;
	for( index = 0; j < i ; )
	{
		newRoute[index++] = curr_tour->path[j++];
	}
	for( index = k; j < kPlus; )
	{
		newRoute[index--] = curr_tour->path[j++];
	}
	for( index = kPlus; j < count; )
	{
		newRoute[index++] = curr_tour->path[j++];
	}
	tour* new_tour = new tour(newRoute);
//	new_tour->cost = map->getTourDistance(new_tour);
//	printTour(curr_tour);
//	cout << "Switch i=" << i << " and k=" << k << endl;
//	printTour(new_tour);
	return new_tour;
}

tour* TabuSearch::swap(tour* t, int from, int to, double cost)
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
	
	t->cost += cost;		
	//~ cout << "After swap" << endl;
	//~ printTour(t);
	
	return t;	
}


double TabuSearch::getNewCost(tour* t, int i1, int i2) {
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
	cost += map->getDistance(city1, right2);	
	cost += map->getDistance(city2, left1);	

	return cost;
}

// Public
int tabu_max = 100;

tour* TabuSearch::getBetterTour(tour* t)
{	
	std::clock_t start = std::clock();   
	t->cost = map->getTourDistance(t);	
	
	int counter = 0;	
	std::clock_t deadline = std::clock() + 1.5*CLOCKS_PER_SEC;
	do
	{
		counter++;
		
		if(!findNewTour(t))
		{		
			if(tabu_list.size() == 0)			
				break;
			else
				tabu_list.clear();
		}
		
		//~ cout << t->cost << endl;
		
		//~ if(counter % 2 == 0)
		//~ {
			//~ tabu_list.clear();
		//~ }
	} while(deadline > std::clock());
	
	//~ cout << "Attempts: " << counter << endl;
	
	return t;	
}

bool TabuSearch::findNewTour(tour* t)
{
	// Tour size
	
	int count = t->path.size();
	// Some initial values
	int cIndex1 = -1;
	int cIndex2 = -1;
	//double bestCostDiff = 0;
	bool changed = false;

	int last_candidate = -1;
	for(int i = 1; i < count; i++) 
	{
		for(int j = i+1; j < count; j++) 
		{
			int candidate = t->path[j];

			if(isTabu(candidate) || i == j)
			{
				continue;
			}
			double diff = getNewCost(t, i, j);
			//if(new_tour->cost < tour_cost)
			if(diff < 0)
			{
				//~ tour* new_tour = flip(t, i, j);
				swap(t, i, j, diff);
				changed = true;
				tabu_move(candidate);
				while(tabu_list.size() > tabu_max)
				{
					expire_move();
				}
			}
		}
	}

	return changed;		
	//~ return t;
}
