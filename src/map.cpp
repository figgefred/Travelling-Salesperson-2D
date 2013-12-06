#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>    // std::sort

#include "types.h"
#include "map.h"
#include "types.h"

using namespace std;

Map::Map (vector<coordinate*>* cities)
{
	dim = cities->size();
	setDistanceMatrix(cities);
	cities->clear();		
	delete cities; // Frigör coordinates etc, vi behöver space för neighbourmaps? :/
	setNeighbourMap();
}

Map::~Map()
{
	for(int i = 0; i < dim; i++)
	{
		delete distance_mat[i];
		//~ delete neighbourMap[i];
	}
	delete distance_mat;	
}

double Map::getDistance(int i, int j)
{
	return distance_mat[i][j];
}

int Map::getDimension()
{
	return dim;
}

double Map::calculateDistance(coordinate* c1, coordinate* c2)
{
	double x = c1->x - c2->x;
	double y = c1->y - c2->y;
	return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

void Map::setDistanceMatrix(std::vector<coordinate*>* cities)
{
	distance_mat = new double*[dim];
	for(int i = 0; i < dim; i++)
	{
		distance_mat[i] = new double[dim];
	}

	for(int i = 0; i < dim; i++)
	{		
		for(int j = i+1; j < dim; j++)
		{
			double d = calculateDistance(cities->at(i), cities->at(j));
			distance_mat[i][j] = d;
			distance_mat[j][i] = d;			
		}
	}
}

void Map::setNeighbourMap() {
	// Adjancency lists...
	vector<double> distances; // = new vector<double>();	// Allokera på heap!!
	//~ distances->reserve(dim);
	double furthestClosestNeighbour = 0.0D;
	int pos = (dim > ADJACENCY_LIST_SIZE) ?  ADJACENCY_LIST_SIZE - 2 : dim - 2;
	
	for(int i = 0; i < dim; ++i) {		
		for(int j = 0; j < dim; ++j) {
			if(i == j) continue;
			distances.push_back(distance_mat[i][j]);
		}
		
		sort(distances.begin(), distances.end());
		
			
		//~ cout << "dim/pos:" << dim << " " << pos << endl;
		furthestClosestNeighbour = distances.at(pos);			
		distance_mat[i][i] = furthestClosestNeighbour;
		distances.clear();
		
		//~ for(int j = 0; j < dim; j++)
			//~ if(i != j && distance_mat[i][j] <= furthestClosestNeighbour)
				//~ closest_neighbours->push_back(j);
				//~ 
		//~ neighbourMap.push_back(closest_neighbours);
		
		//~ cout << "len: " << closest_neighbours.size() << " ";
		//~ for ( auto it = closest_neighbours.begin(); it != closest_neighbours.end(); ++it )
			//~ std::cout << " " << *it;
		//~ 
	}
	
	//~ delete distances;
}

double Map::getTourDistance(vector<int>& nodes)
{
	//~ cout << "Getting tour distance" << endl;
	double c = 0;
	int N = nodes.size();
	for(int i = 1; i < N; i++)
	{
		c += getDistance(nodes[i-1], nodes[i]);
	}
	c += getDistance(nodes[N-1], nodes[0]);
	return c;
}

double Map::getTourDistance(tour* t) {
	return getTourDistance(t->path);
}

vector<int>* Map::getNeighbourhood(int cityID) {
	return neighbourMap[cityID];
}
