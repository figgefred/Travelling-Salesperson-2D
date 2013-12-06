#include <iostream>
#include <math.h>
#include <vector>
#include "neighbourhood.h"
#include "types.h"
#include "map.h"

using namespace std;

Map::Map (vector<coordinate*> cities)
{
	this->cities = cities;
	dim = cities.size();
	setDistanceMatrix();
	setLocalNeighbourhoods();
}

Map::~Map()
{
	for(int i = 0; i < dim; i++)
	{
		delete distance_mat[i];
		delete closestNeighbours[i];
	}
	delete distance_mat;
}

vector<coordinate*> Map::getCities()
{
	return cities;
}

double Map::getDistance(int i, int j)
{
	return distance_mat[i][j];
}

int Map::getDimension()
{
	return dim;
}
	
coordinate* Map::getCityCoordinate(int i)
{
	return cities[i];
}

double Map::calculateDistance(coordinate* c1, coordinate* c2)
{
	double x = c1->x - c2->x;
	double y = c1->y - c2->y;
	return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

void Map::setLocalNeighbourhoods()
{
	int dim = getDimension();
	int maxNeighbours = 50;
	maxNeighbours = (maxNeighbours>=dim?dim-1:maxNeighbours);
	
	//closestNeighbours = vector<Neighbourhood*>[dim];
	for(int i = 0; i < dim; i++)
	{
		closestNeighbours.push_back(new Neighbourhood(i, dim, maxNeighbours, distance_mat[i]));
	}
}

void Map::setDistanceMatrix()
{
	distance_mat = new double*[dim];
	for(int i = 0; i < dim; i++)
	{
		distance_mat[i] = new double[dim];
	}
	for(int i = 0; i < dim; i++)
	{
		for(int j = i; j < dim; j++)
		{
			if(i == j)
			{
				continue;
			}
			double d = calculateDistance(cities[i], cities[j]);
			distance_mat[i][j] = d;
			distance_mat[j][i] = d;
		}
	}
}

Neighbourhood* Map::getNeighbourhood(int index)
{
	return closestNeighbours[index];
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

void Map::setTourDistance(tour* t)
{
	t->cost = getTourDistance(t->path);
}
