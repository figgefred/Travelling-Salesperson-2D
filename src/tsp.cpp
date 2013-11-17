
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <math.h>
#include <fstream>

#include "map.h"
#include "types.h"

using namespace std;

#define PRINT

//double** distance_mat;
Map* map;


void print_usage(string);
vector<coordinate*>* getCitiesFromSTDin();
vector<int> getPathFromFile(string);
tour* naiveTspPath();
void setCost(tour*);
void printMapMatrix();
void printMapCities();
// Prims algoritm.
vector<coordinate> minSpanTree();

int main(int argc, char* argv[])
{
	vector<coordinate*> cities = *(getCitiesFromSTDin());
	int count = cities.size();
	if(cities.size() == 0)
	{
		exit(0);
	}

	map = new Map(cities);

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
			int count = tmp.size();
			for(int i = 0; i < count; i++) 
			{
				cout << tmp[i] << " ";
			}
			cout << "\n";
		#endif

		setCost(t);
		cout << "\nCost of path is " << t->cost << "\n";

		delete t;
		exit(0);
	}

	tour* tour = naiveTspPath();

	cout << "\nOPTIMAL COST: " << tour->cost << "\n\n";

	for(int i = 0; i < count; i++)
	{
		cout << tour->path[i] << "\n";
	}
	
	cout << "\nMIN Spanning Tree: " << endl;
	vector<coordinate> tree = minSpanTree();

	// Free resources
	delete map;
	delete tour;
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

void setCost(tour* t)
{
	double c = 0;
	int N = t->path.size();
	for(int i = 1; i < N; i++)
	{
		c += map->getDistance(t->path[i-1], t->path[i]);
	}
	t->cost = c;
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
			{
				best = j;
				cost = d;
			}
		}
		t[i] = best;
		used[best] = true;
		totalcost += cost;
	}
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

	vector<int> tour (count, count);

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

// Prims algortihm.
vector<coordinate> minSpanTree() {
	vector<coordinate*> cities = map->getCities();
	// reusing coordinate struct here.
	vector<coordinate> edges;
	unordered_set<coordinate*> pickedCities;
	
	// find initial edge. Min of first city feels like a good guess..
	coordinate best(-1,-1);
	double _min = 100000.0D; // arbitary large number for now.
	for(unsigned int i = 1; i < cities.size(); ++i)
	{
		double dist = map->getDistance(0, i);
		if(dist < _min) {
			_min = dist;
			best = coordinate(0,i);
		}
	}

	cout << best.x << "," << best.y <<  " " << _min << endl;	
	edges.push_back(best);
	pickedCities.insert(cities[best.x]);
	pickedCities.insert(cities[best.y]);

	while(pickedCities.size() < cities.size()) {
		
		// find min edge (u,v) where u exists in pickedCities and v does not.
		_min = 1000000.0D;
		for(unsigned int u = 1; u < cities.size(); ++u)
		{
			if(pickedCities.count(cities[u]) > 0)
				continue;
				
			for(unsigned int v = 0; v < cities.size(); ++v) {
				if(u == v || pickedCities.count(cities[v]) == 0)
					continue;
			
				double dist = map->getDistance(u, v);
				if(dist < _min) {
					_min = dist;
					best = coordinate(u,v);
				}
			}
		}
		
		
		edges.push_back(best);
		pickedCities.insert(cities[best.x]);
		cout << best.x << "," << best.y <<  " " << _min << " " << pickedCities.size() << endl;	
	}
	
	
	return edges;
}

void print_usage(string output)
{
	string s = "USAGE: " + output + " <inputfile for path> ";
	cout << s;
	exit(0);
}
