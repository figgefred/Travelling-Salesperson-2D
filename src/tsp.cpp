
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

using namespace std;

#define PRINT
//#define KATTIS

//double** distance_mat;
Map* map;
LocalSearch* local_search;

void print_usage(string);
vector<coordinate*>* getCitiesFromSTDin();
vector<int> getPathFromFile(string);
tour* naiveTspPath();
void printMapMatrix();
void printMapCities();
void printTour(tour*);


int main(int argc, char* argv[])
{
	vector<coordinate*> cities = *(getCitiesFromSTDin());
	int count = cities.size();
	if(cities.size() == 0)
	{
		exit(0);
	}

	map = new Map(cities);
	local_search = new TabuSearch(map, cities);


	#ifdef PRINT
		printMapCities();
		printMapMatrix();
	#endif

	if(argc > 1)
	{
		vector<int> tmp = getPathFromFile(argv[1]);
		tour* t = new tour(tmp, 0);
	
		#ifdef PRINT
			cout << "PATH ";
			count = tmp.size();
			for(int i = 0; i < count; i++) 
			{
				cout << tmp[i] << " ";
			}
			cout << "\n";
		#endif

		map->setTourDistance(t);
		cout << "\nCost of path is " << t->cost << "\n";

		delete t;
		exit(0);
	}

	tour* curr_tour= naiveTspPath();

	#ifdef PRINT
		cout << "\nNaive path: \n";
		printTour(curr_tour);
	#endif

	tour* better_tour = local_search->getBetterTour(curr_tour);
	if(better_tour->cost < curr_tour->cost)
	{
		delete curr_tour;
		curr_tour= better_tour;
	}
	else
	{
		delete better_tour;
	}
	#ifdef PRINT
		cout << "\nLocal search path: \n";
		printTour(curr_tour);
	#endif

#ifndef KATTIS
	cout << "End result: \n";
#endif
	printTour(curr_tour);

	
//	christofides(map);

	// Free resources
	delete local_search;
	delete map;
	delete curr_tour;
}

void printTour(tour* t)
{
	int count = t->path.size();
	#ifdef KATTIS
		for(int i = 0; i < count; i++)
		{
			cout << t->path[i] << "\n";
		}
		cout << "\n";
	#else
		cout << t->path[0];
		for(int i = 1; i < count; i++)
		{
			cout << " -> " << t->path[i];
		}
		cout << "\n";
		cout << "COST: " << t->cost << "\n";
	#endif
}

void printMapCities()
{
	cout << "\n\nCITIES \n";
	vector<coordinate*> cities = map->getCities();
	int count = map->getCityCount();
	for(int i = 0; i < count; i++)
	{
		cout << "[" << i << "]: (" << cities[i]->x << ", " << cities[i]->y << ") \n";
	}
}

void printMapMatrix()
{
	cout << "\n\nDISTANCE MATRIX \n";
	int count = map->getCityCount();
	for(int i = 0; i < count; i++)
	{
		for(int j = 0; j < count; j++)
		{
			cout << map->getDistance(i, j) << " ";
		}
		cout << "\n";
	}
}

// Kattis naive algorithm: https://kth.kattis.scrool.se/problems/oldkattis:tsp
tour* naiveTspPath()
{
	int N = map->getCityCount();
	bool used[N];

	vector<int> t(N, N);

	used[0] = true;
	t[0] = 0;

	double cost;
	double totalcost = 0;

	int best;
	double d;
	for(int i = 1; i < N; i++)
	{
		best = -1;
		cost = 0;
		for(int j = 0; j < N; j++)
		{
			d = map->getDistance(t[i-1], j);
			if(!used[j] && (best == -1 || d < cost))
	//s	if(!used[j] && (best == -1 || d > cost))
			{
				best = j;
				cost = d;
			}
		}
		t[i] = best;
		used[best] = true;
		totalcost += cost;
	}

	// Add last step back to origin
	totalcost += map->getDistance(t[N-1], t[0]);
	return new tour(t, totalcost);
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


coordinate* newCoordinate(string s)
{
    string buf; 			// Have a buffer string
    stringstream ss(s); 	// Insert the string into a stream

    string tmp[2];  // Create vector to hold our words

    ss >> tmp[0];
    ss >> tmp[1];

    // close string stream?

    return new coordinate(atof(tmp[0].c_str()), atof(tmp[1].c_str()));
}



void print_usage(string output)
{
	string s = "USAGE: " + output + " <inputfile for path> ";
	cout << s;
	exit(0);
}
