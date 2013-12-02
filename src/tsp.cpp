
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

//#define PRINT
#define KATTIS

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
	local_search = new TabuSearch(map);

	#ifdef PRINT
		printMapCities();
		cout << "DONE CITIES! \n";
		printMapMatrix();
		cout << "DONE PRINT! \n";
	#endif
	
	tour* curr_tour= naiveTspPath();

	#ifdef PRINT
		cout << "\nNaive path: \n";
		printTour(curr_tour);
	#endif

	bool done = false;
/*	int max = 10;
	int counter = 1;
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
	#ifdef PRINT
		cout << "\nLocal search path: \n";
		printTour(curr_tour);
	#endif

#ifndef KATTIS
	cout << "End result: \n";
#endif
*/

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

// Kattis naive algorithm: https://kth.kattis.scrool.se/problems/oldkattis:tsp
tour* naiveTspPath()
{
	int N = map->getDimension();
	bool used[N];

	// Init array
	for(int i = 1; i < N; i++)
	{
		used[i] = false;
	}
	used[0] = true;
	tour* newTour = new tour(N);
	
	//t[0] = 0;
	newTour->path[0] = 0;

	double cost;
	double totalcost = 0.0;

	int best;
	double d;
	for(int i = 1; i < N; i++)
	{
		best = -1;
		cost = 2147483647;
		for(int j = 0; j < N; j++)
		{
			if(i-1 == j)
				continue;
			d = map->getDistance(newTour->path[i-1], j);

			/*if(i == 8)
			{
				cout << "i = " << i << ", i-1 = " << (i-1) << " j = " << j << " d " << d << " currCost = " << cost;
				cout << "used is " << used[j];
				cout << " BADAM!! \n\n";
			}*/

			//s	if(!used[j] && (best == -1 || d > cost))
			if(!used[j] && (best == -1 || d < cost))
			{
				best = j;
				cost = d;
			}
		}
		newTour->path[i] = best;
		used[best] = true;
		totalcost += cost;
		
		/*if(best == -1) {
			cout << "i = " << i << " ";
			cout << " BADAM!! \n\n";
		}*/
	}

	// Add last step back to origin
	totalcost += map->getDistance(newTour->path[N-1], newTour->path[0]);
	newTour->cost = totalcost;
	//exit(0);
	return newTour;
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
