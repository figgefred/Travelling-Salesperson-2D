
#include <math.h>
#include <vector>

#include "types.h"
#include "map.h"
#include "types.h"

using namespace std;

Map::Map (vector<coordinate*> cities)
{
	this->cities = cities;
	setDistanceMatrix();
}

Map::~Map()
{
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

int Map::getCityCount()
{
	return cities.size();
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

void Map::setDistanceMatrix()
{
	int count = getCityCount();
	distance_mat = new double*[count];
	for(int i = 0; i < count; i++)
	{
		distance_mat[i] = new double[count];
	}

	for(int i = 0; i < count; i++)
	{
		for(int j = i; j < count; j++)
		{
			if(i == j)
				continue;

			double d = calculateDistance(cities[i], cities[j]);
			distance_mat[i][j] = d;
			distance_mat[j][i] = d;
		}
	}
}