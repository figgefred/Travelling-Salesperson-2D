
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
	//int count = m->getDimension();
	//tabu_list;
	/*for(int i = 0; i < count; i++)
	{
		tabu_list[i] = new int[count];
		for(int j = 0; j < count; j++)
		{
			tabu_list[i][j] = 0;
		}
	}*/
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

//swaps two cities
void TabuSearch::swap(vector<int>* t, int i1, int i2)
{
	// Do switch
    int tmp = (*t)[i1];
    (*t)[i1] = (*t)[i2];
    (*t)[i2] = tmp;
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

	/*cost -= map->getDistance(city1, left1);		
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
	
	*/
	return cost;
}

// Public
int tabu_max = 10;

tour* TabuSearch::getBetterTour(tour* t)
{	
	std::clock_t start = std::clock();   
	t->cost = map->getTourDistance(t);	
	int max = 10;
	int counter = 0;
	bool timeout = false;
	do
	{
		timeout = false;//(( std::clock() - start ) / (double) CLOCKS_PER_SEC) > 1.0;
		counter++;
		tour* newTour = findNewTour(t);
		if(newTour == NULL)
		{
		//	continue;
			break;
		}
		delete t;
		t = newTour;
		if(counter % 2 == 0)
		{
			tabu_list.clear();
		}
	//} while(!timeout);
	//cout << "Ran " << counter << " rounds!" << endl;
	} while(true && counter < max);
	return t;	
}

tour* TabuSearch::findNewTour(tour* curr_tour)
{
	// Tour size
	int count = curr_tour->path.size();
	vector<int> tmpTour(count, count);
	for(int i = 0; i < count; i++)
	{
		tmpTour[i] = curr_tour->path[i];
	}
	tour* t = new tour(tmpTour);
	double tour_cost = curr_tour->cost;
	t->cost = tour_cost;
	

	// Some initial values
	int cIndex1 = -1;
	int cIndex2 = -1;
	//double bestCostDiff = 0;
	bool changed = false;

	for(int i = 1; i < count; i++)
	{
		//cout << "Index " << i << endl;
//		Neighbourhood* neighbourhood = map->getNeighbourhood(tmpTour[i]);
		for(int j = i+1; j < count; j++)//int j = 0; j < neighbourhood->getNeighbourCount(); j++)
		{
			int candidate = t->path[j];
/*			if(!neighbourhood->containsNeighbour(candidate))
			{
				continue;
			}*/

			if(tabu_list.find(candidate) != tabu_list.end() || i == j)
			{
				continue;
			}
			double diff = getNewCost(t, i, j);
			//if(new_tour->cost < tour_cost)
			if(diff < 0)
			{
				tour* new_tour = flip(t, i, j);
				changed = true;
				tabu_move(candidate);
				while(tabu_list.size() > tabu_max)
				{
					expire_move();
				}
				//tabu_list.insert(t->path[i]);
				//swap(&tmpTour, i, j);
				delete t;
				t = new_tour;
				tour_cost += diff;
			}

/*			double cDiff = getNewCost(t, i, j);
			if(cDiff < 0)//bestCostDiff)
			{
				//firstNeighbour = false;
				//cIndex1 = i;
				//cIndex2 = j;
				changed = true;
				tabu_move(candidate);
				while(tabu_list.size() > tabu_max)
				{
					expire_move();
				}
				//tabu_list.insert(t->path[i]);
				//swap(&tmpTour, i, j);
				tour* new_tour = flip(t, i, j);
				delete t;
				t = new_tour;
				tour_cost += cDiff;
			}*/
		}
	/*	if(tabu_counter > tabu_max)
		{
			tabu_counter = 0;
			tabu_list.clear();
		}*/
		/*if(tabu_list.size() > 10)
		{
			tabu_list.clear();
		}*/
	}

	if(!changed)//cIndex1 == -1)
		return NULL;
	//cout << "Wohoooooo lets switch cIndex1=" << cIndex1 << " with cIndex2=" << cIndex2 << endl;
	//tabu_list[cIndex1][cIndex2]++;
	//tabu_list[cIndex2][cIndex1]++;
	//tour* t = new tour(tmpTour);
	t->cost = tour_cost;
	return t;
}

void TabuSearch::reset()
{

}

/*int main()
{
	vector<coordinate*> cities;
	cities.push_back(new coordinate(1.0, 1.0));
	cities.push_back(new coordinate(2.0, 2.0));
	Map* map = new Map(cities);

	LocalSearch* search = new TabuSearch(map, cities);

	vector<int> t;
	t.push_back(0);
	t.push_back(1);
	tour* ttt = new tour(t, 2);
	cout << "Tour size " << ttt->path.size();
	cout <<"\n";
	for(int i = 0; i < ttt->path.size(); i++)
	{
		cout <<ttt->path[i] << " ";
	}

	search->getBetterTour(ttt);

	cout <<"\n";
	for(int i = 0; i < ttt->path.size(); i++)
	{
		cout <<ttt->path[i] << " ";
	}
	cout <<"\n";


}*/

