
//#include <math.h>
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
	//double d = map->getDistance(c1, c2);
	//tabu_list.insert(edge(c1, c2, d));
	//tabu_order.push_back(edge(c1, c2, d));
	tabu_record[c1][c2] += 1;
	tabu_record[c2][c1] += 1;
	tabu_order.push_back(c1);
	tabu_order.push_back(c2);
}

bool TabuSearch::isTabu(int c1, int c2)
{
	//return tabu_list.find(edge(c1, c2, map->getDistance(c1, c2))) != tabu_list.end();
	return tabu_record[c1][c2] != 0;
}

pair<int, int> TabuSearch::popTabu()
{
	std::pair<int, int> edge;

	edge = make_pair( *(tabu_order.begin()), *(++tabu_order.begin()));
	expire_move();
	return edge;
}

void TabuSearch::expire_move()
{
	int c1 = tabu_order.front();
	tabu_order.pop_front();
	int c2 = tabu_order.front();
	tabu_order.pop_front();
	//while(tabu_record[c1][c2] == 0)
	//{
	//	c1 = tabu_order.front();
		//tabu_order.pop_front();
		// = tabu_order.front();
		//tabu_order.pop_front();
	//}
	tabu_record[c1][c2] -= 1;
	tabu_record[c2][c1] -= 1;
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
int tabu_max = 10;

tour* TabuSearch::getBetterTour(tour* t)
{	
	std::clock_t start = std::clock();   
	t->cost = map->getTourDistance(t);	
		
	int N = t->path.size();
	if(tabu_max > N/2)
		tabu_max = N/2;


	int counter = 0;	
	std::clock_t deadline = std::clock() + 1.5*CLOCKS_PER_SEC;
	do
	{
		counter++;
		
		if(!findNewTour(t))
		{		
			if(tabu_order.size() == 0)			
				break;
			else
			{
				// Initiate default aspiration behavior
				expire_move();

				// Copy tour and fetch an edge to swap
				//int count = t->path.size();
				/*vector<int> tmp(count, count);
				tour* newTour = new tour(tmp);
				for(int i = 0; i < count; i++)
				{
					newTour->path[i] = t->path[i];
				}*/
				
				/*double diff = 0.0;
				pair<int, int> edge;
				do
				{
					edge = popTabu();
					diff = getNewCost(t, edge.first, edge.second);
				} while(tabu_order.size() != 0);*/
			}
		}
		while(tabu_order.size() > tabu_max)
		{
			expire_move();
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
	double bestDiff = 0.0;
	//bool changed = false;

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
			//if(new_tour->cost < tour_cost)
			if(diff < bestDiff)
			{
				cIndex1 = i;
				cIndex2 = j;
				bestDiff = diff;
				//~ tour* new_tour = flip(t, i, j);
				/*swap(t, i, j, diff);
				changed = true;
				tabu_move(candidate);
				tabu_move(t->path[i]);
				while(tabu_list.size() > tabu_max)
				{
					expire_move();
				}*/
			}
		}
	}
	if(bestDiff != 0.0)
	{
		swap(t, cIndex1, cIndex2, bestDiff);
		tabu_move(t->path[cIndex1], t->path[cIndex2]);
		return true;
	}
	else
	{
		return false;
	}
	
	//~ return t;
}
