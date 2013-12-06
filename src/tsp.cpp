
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <fstream>
#include <ctime>

#include "map.h"
#include "types.h"
#include "christofides.h"
#include "localsearch.h"
#include "tabusearch.h"
#include "naivegreedy.h"
#include "2opt.h"

using namespace std;

#define KATTIS
//#define DEBUG_TRACE

Map* map;

void print_usage(string);
vector<coordinate*>* getCitiesFromSTDin();

int main()
{
	std::clock_t deadline = std::clock() + 1.9*CLOCKS_PER_SEC;
	vector<coordinate*>* cities = getCitiesFromSTDin();
	if(cities->size() == 0)
	{
		return 0;
	}
	
	if(cities->size() == 1)
	{
		cout << 0 << endl;
		return 0;
	}

	map = new Map(cities);
	//~ LocalSearch* local_search = new TabuSearch(map);
	LocalSearch* local_search = new TwoOpt(map);
	NaiveGreedy* greedy = new NaiveGreedy;
	// christofides(map);		
	
	tour* best_tour = NULL;
	double bestcost = 0;
	
	int i = 0;
	for(; std::clock() < deadline; i++)
	{
		i = i % map->getDimension();
		// Startgissning
		tour* curr_tour = greedy->naiveTspPath(map, i);
		// Förbättring
		curr_tour = local_search->getBetterTour(curr_tour, deadline);
		
		//~ cout << i << " " << curr_tour->cost << endl;
		
		if(best_tour == NULL || curr_tour->cost < bestcost) {
			bestcost = curr_tour->cost;
			best_tour = curr_tour;			
		}
		
		//~ delete curr_tour;
	}
	
	
	// Output.
	printTour(best_tour);
	
	//~ cout << "Runs: " << i << endl;
	
	
	// Free resources
	delete local_search;
	delete map;
	
}

vector<coordinate*>* getCitiesFromSTDin()
{
	string line;
	getline(cin, line);
	int count = atoi(line.c_str());

	vector<coordinate*>* cities = new vector<coordinate*>();

	for(int i = 0; i < count; i++)
	{
		getline(cin, line);
		cities->push_back(newCoordinate(line));
	}

	return cities;
}
