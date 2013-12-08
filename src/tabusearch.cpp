
#include <cmath>
#include <vector>
#include <utility>	// pair
#include <stdlib.h>
#include <iostream> // cout
#include <unordered_set>
#include <list>

#include "types.h"
#include "map.h"
#include "tabusearch.h"

#include <ctime>

using namespace std;

int tabu_delay = 5;
std::clock_t deadline;
const int MAX_INT = 2147483647;
const double graunularity = 0.00001;

TabuSearch::TabuSearch(Map* m)
{
	map = m;
	tabu_dim = map->getDimension();
	tabu_record = new int*[tabu_dim];
	for(int i = 0; i < tabu_dim; i++)
	{
		tabu_record[i] = new int[tabu_dim];
		for(int j = 0; j < tabu_dim; j++)
		{
			tabu_record[i][j] = 0;  
		}
		//tabu_count.push_back(0);
	}
}

TabuSearch::~TabuSearch()
{
	for(int i = 0; i < tabu_dim; i++)
	{
		delete tabu_record[i];
	}
	delete tabu_record;
}

// Private
void TabuSearch::tabu_move(int c1, int c2)
{
	tabu_record[c1][c2] += tabu_delay;
	tabu_record[c2][c1] += tabu_delay;
	tabu_list.push_back(city_edge(c1, c2));
}

bool TabuSearch::isTabu(int c1, int c2)
{
	return tabu_record[c1][c2] != 0;
}

void TabuSearch::expire_move()
{
	vector<city_edge> toRemove;
	for(auto itr = tabu_list.cbegin(); itr != tabu_list.cend(); ++itr)
	{
		city_edge e = *(itr);
		tabu_record[e.c1][e.c2] -= 1;
		tabu_record[e.c2][e.c1] -= 1;
		if(tabu_record[e.c1][e.c2] == 0)
		{
		//	tabu_list.erase(*itr);
			toRemove.push_back(e);
		}
	}

	// Clear
	for(int i = 0; i < toRemove.size(); i++)
	{
		tabu_list.remove(toRemove[i]);
	}
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

tour* TabuSearch::getBetterTour(tour* initTour, std::clock_t d)
{	
	std::clock_t start = std::clock();   
	initTour->cost = map->getTourDistance(initTour);	
		
	int N = initTour->path.size();
	if(tabu_delay > N/2)
		tabu_delay = N/2;

	tour* bestTour = new tour(initTour->path);
	bestTour->cost = initTour->cost;

	tour* t = new tour(initTour->path);
	t->cost = initTour->cost;

	int counter = 0;	
	//std::clock_t deadline = std::clock() + 1.5*CLOCKS_PER_SEC;
	deadline = d;
	do
	{
		counter++;
	//	cout << "findNewTour - START Time: " << std::clock()/((double)CLOCKS_PER_SEC) << endl;
		bool foundTour = findNewTour(t);
	//	cout << "findNewTour - END Time: " << std::clock()/((double)CLOCKS_PER_SEC) << endl;
		if(!foundTour)
		{
			if(tabu_list.size() == 0)			
			{
				delete t;
				return bestTour;
			}
			else
			{
				expire_move();
				continue;
			}
		}
		double newCost = t->cost;
		if(newCost < bestTour->cost)
		{
			//cout << endl;
	 		//cout << "OLD cost=" << bestTour->cost << " vs new cost=" << newCost << endl;
		//	delete bestTour;
			bestTour->path = t->path;//new tour(t->path);
			bestTour->cost = newCost;			
		//bestTour = t;
			//cout << "NEW SOLUTION cost=" << t->cost << "tabu_count=" << tabu_list.size() << endl;
			//cout << "Current Tabu: {";
			/*for(auto itr = tabu_list.cbegin(); itr != tabu_list.end(); ++itr)
			{
				edge e = *(itr);
				cout << "(" << e.c1 << ", ";
				cout << e.c2 << "), ";
			}
			cout << "}" << endl;*/
		}
		else
		{
			//cout << "NO SOLUTION cost=" << t->cost << "tabu_count=" << tabu_list.size() << endl;
		}
		expire_move();
	//	cout << "Time: " << std::clock()/((double)CLOCKS_PER_SEC) << endl;
	} while(deadline > std::clock());
	//cout << "TABUUUU-Attempts: " << counter << endl;
	if(t->cost < bestTour->cost)
	{
		delete bestTour;
		return t;
	}
	return bestTour;	
}

bool TabuSearch::findNewTour(tour* t)
{
// Tour size
	int count = t->path.size();
// Some initial values
	int cIndex1 = -1;
	int cIndex2 = -1;
	double bestDiff = MAX_INT;
	bool first = false;

	int last_candidate = -1;
	for(int i = 1; i < count; i++) 
	{
		for(int j = i+1; j < count; j++) 
		{
			int candidate = t->path[j];
			if(isTabu(t->path[i], candidate))
			{
				continue;
			}
			double diff = getNewCost(t, i, j);
			if(diff < bestDiff)//bestDiff || first)//&& abs(diff - bestDiff) > graunularity )
			{
				first = false;
				cIndex1 = i;
				cIndex2 = j;
				bestDiff = diff;
			}
		}
	}
	if(cIndex1 != -1)//bestDiff != MAX_INT)
	{
		swap(t, cIndex1, cIndex2, bestDiff);
		tabu_move(t->path[cIndex1], t->path[cIndex2]);
		return true;
	}
	else
	{
		return false;
	}
}
