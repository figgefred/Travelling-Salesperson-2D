#include "christofides.h"

#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

// http://en.wikipedia.org/wiki/Christofides_algorithm
tour christofides(Map* map) {
	cout << "\nMIN Spanning Tree: " << endl;
	vector<coordinate> tree = minSpanTree(map);
	
	int degree_count[map->getCities().size()];
	for(unsigned int i = 0; i < map->getCities().size(); ++i)
		degree_count[i] = 0;
	
	for(unsigned int i = 0; i < tree.size(); ++i)
	{
		coordinate edge = tree[i];
		int x = (int) edge.x;
		int y = (int) edge.y;
		degree_count[x] = degree_count[x]++;
		degree_count[y] = degree_count[y]++;
	}
	
	vector<coordinate*> odd_degree_cities;
	for(unsigned int i = 0; i < map->getCities().size(); i++)
		if(degree_count[i] % 2 == 1) {
			cout << i << endl;
			odd_degree_cities.push_back(map->getCities()[i]);
		}

	vector<int> p;
	double c = 0.5d;
	tour t(p, c);
	return t;
	
}

// Prims algortihm.
vector<coordinate> minSpanTree(Map* map) {
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
