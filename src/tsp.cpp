
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
#include "minspan.h"
#include "localsearch.h"
#include "tabusearch.h"
#include "naivegreedy.h"
#include "2opt.h"
#include "simulatedannealing.h"

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
	//~ LocalSearch* local_search = new SimulatedAnnealing(map);
	NaiveGreedy* greedy = new NaiveGreedy;
	
	tour* best_tour = new tour;
	best_tour->cost = -1;
	
	int i = 0;
	int improvements = 0;
	for(; std::clock() < deadline; i++)
	{
		//~ i = i % map->getDimension();
		
		// Startgissning
		tour* curr_tour = greedy->naiveTspPath(map, rand() % map->getDimension());
		//~ tour* curr_tour = approxTSP(map);
		
		// Förbättring
		curr_tour = local_search->getBetterTour(curr_tour, deadline);
		
		//~ cout << i << " " << curr_tour->cost << endl;
		cout << curr_tour->cost << endl;
		
		if(best_tour->cost < 0 || curr_tour->cost < best_tour->cost) {
			best_tour->path = curr_tour->path;			
			best_tour->cost = curr_tour->cost;
			improvements++;
			
		}		
		
		delete curr_tour;
	}
	cout << improvements << endl;
	// Output.
	//~ printTour(best_tour);
	
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
