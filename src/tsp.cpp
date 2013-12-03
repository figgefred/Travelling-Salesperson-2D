
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <fstream>

#include "map.h"
#include "types.h"
#include "christofides.h"
#include "localsearch.h"
#include "tabusearch.h"
#include "naivegreedy.h"
#include "2opt.h"

using namespace std;

//#define PRINT
#define KATTIS
//#define DEBUG_TRACE

Map* map;

void print_usage(string);
vector<coordinate*>* getCitiesFromSTDin();
vector<int> getPathFromFile(string);
void printMapMatrix();
void printMapCities();



int main(int argc, char* argv[])
{
	vector<coordinate*> cities = *(getCitiesFromSTDin());
	if(cities.size() == 0)
	{
		exit(0);
	}

	map = new Map(cities);
	//~ LocalSearch* local_search = new TabuSearch(map);
	LocalSearch* local_search = new TwoOpt(map);
	NaiveGreedy greedy;

	#ifdef PRINT
		printMapCities();
		cout << "DONE CITIES!" << endl;
		printMapMatrix();
		cout << "DONE PRINT!" << endl;
	#endif
	
	#ifdef DEBUG_TRACE
		cout << "Done parsing" << endl;
	#endif
	
	tour* curr_tour= greedy.naiveTspPath(map);
	
	#ifdef DEBUG_TRACE
		cout << "Done Touring" << endl;
	#endif

	#ifdef PRINT
		cout << "\nNaive path: \n";
		printTour(curr_tour);
	#endif

	/*
	bool done = false;
	int max = 2;
	int counter = 0;
	while(!done && counter < max)
	{
		tour* better_tour = local_search->getBetterTour(curr_tour);
		if(better_tour->cost < curr_tour->cost)
		{
			delete curr_tour;
			curr_tour= better_tour;
		}
		else
		{
			done = true;
		}
		counter++;
	}
	* */
	curr_tour = local_search->getBetterTour(curr_tour);

	printTour(curr_tour);

	#ifdef DEBUG_TRACE
		cout << "Finished after counter == " << counter << " were max at " << max << endl;
	#endif

	
//	christofides(map);

	// Free resources
	//~ delete local_search;
	//~ delete map;
	//~ delete curr_tour;
}

void printMapCities()
{
	cout << "\n\nCITIES \n";
	vector<coordinate*> cities = map->getCities();
	int count = map->getDimension();
	for(int i = 0; i < count; i++)
	{
		cout << "[" << i << "]: (" << cities[i]->x << ", " << cities[i]->y << ") \n";
	}
}

void printMapMatrix()
{
	cout << "\n\nDISTANCE MATRIX \n";
	int count = map->getDimension();
	for(int i = 0; i < count; i++)
	{
		for(int j = 0; j < count; j++)
		{
			cout << map->getDistance(i, j) << " ";
		}
		cout << "\n";
	}
}

vector<int> getPathFromFile(string filename)
{
	string line;
	ifstream file(filename.c_str());
	
	if(!file.is_open())
	{
		print_usage("FUNKA INTE JU. DUM FIL");
	}
	
	getline(file, line);
	int count = atoi(line.c_str());

	vector<int> tour(count, count);

	for(int i = 0;i < count; i++)
	{

		getline(file, line);
		tour[i] = atoi(line.c_str());
	}

	file.close();
//	delete file;
	return tour;
}

vector<coordinate*>* getCitiesFromSTDin()
{
	string line;
	getline(cin, line);
	int count = atoi(line.c_str());

	vector<coordinate*>* cities = new vector<coordinate*>();

	for(int i = 0;i < count; i++)
	{

		getline(cin, line);
		(*cities).push_back(newCoordinate(line));
	}

	return cities;
}

void print_usage(string output)
{
	string s = "USAGE: " + output + " <inputfile for path> ";
	cout << s;
	exit(0);
}
