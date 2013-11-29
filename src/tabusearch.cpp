
//#include <math.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

#include "types.h"
#include "map.h"
#include "tabusearch.h"

using namespace std;

TabuSearch::TabuSearch(Map* m, vector<coordinate*> c)
{
	map = m;
	cities = c;
	int count = cities.size();
	for(int i = 0; i < count; i++)
	{
		tabulist.push_back( new int[count] );
	}
}

TabuSearch::~TabuSearch()
{
	int count = tabulist.size();
	for(int i = 0; i < count; i++)
	{
		delete tabulist[i];
	}
}

// Private

//swaps two cities
void TabuSearch::swap(int cityIndex1, int cityIndex2, tour* t)
{
    int tmp = t->path[cityIndex1];
    t->path[cityIndex1] = t->path[cityIndex2];
    t->path[cityIndex2] = tmp;

    map->setTourDistance(t);
}


// Public


tour* TabuSearch::getBetterTour(tour* t)
{
	// Copy initial tour
	int count = t->path.size();
	tour* bestTour = new tour(vector<int>(count));
	for(int i = 0; i <count ; i++ )
	{
		bestTour->path[i] = t->path[i];
	}
	bestTour->cost = t->cost;

	// Some initial values
	int city1 = 0;
	int city2 = 0;
	bool firstNeighbour = true;

	for(int i = 1; i < count; i++)
	{
		for(int j = 1; j < count; j++)
		{
			if(i == j)
				continue;

			// Copy current best
			tour* tourCandidate = new tour(vector<int>(count));
			for(int i = 0; i <count ; i++ )
			{
				tourCandidate->path[i] = bestTour->path[i];
			}
			swap(i, j, tourCandidate);

			if(bestTour->cost > tourCandidate->cost && tabulist[i][j] == 0)
			{
				firstNeighbour = false;
				city1 = i;
				city2 = j;
				tour* tmp = bestTour;
				bestTour = tourCandidate;

		cout << bestTour->path[0];
		for(int i = 1; i < count; i++)
		{
			cout << " -> " << bestTour->path[i];
		}
		cout << "\n";
		cout << "COST: " << bestTour->cost << "\n";
				
				delete tmp;
			}
			else
			{
				delete tourCandidate;
			}
		}
	}
	if(city1 == 0)
	{
		tabulist[city1][city2]++;
		tabulist[city2][city1]++;
	}

	return bestTour;
}

void TabuSearch::reset()
{
	int count = tabulist.size();
	for(int i = 0; i < count; i++)
	{
		for(int j = 0; j < count; j++)
		{
			tabulist[i][j] = 0;
		}
	}
}

/*int main()
{
	vector<coordinate*> cities;
	cities.push_back(new coordinate(1.0, 1.0));
	cities.push_back(new coordinate(2.0, 2.0));
	Map* map = new Map(cities);

	LocalSearch* search = new TabuSearch(map, cities);

	vector<int> t;
	t.push_back(0);
	t.push_back(1);
	tour* ttt = new tour(t, 2);
	cout << "Tour size " << ttt->path.size();
	cout <<"\n";
	for(int i = 0; i < ttt->path.size(); i++)
	{
		cout <<ttt->path[i] << " ";
	}

	search->getBetterTour(ttt);

	cout <<"\n";
	for(int i = 0; i < ttt->path.size(); i++)
	{
		cout <<ttt->path[i] << " ";
	}
	cout <<"\n";


}*/

