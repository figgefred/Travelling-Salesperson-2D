
//#include <math.h>
#include <vector>
#include <stdlib.h>
#include <iostream>


#include "types.h"
#include "map.h"
#include "tabusearch.h"

using namespace std;

TabuSearch::TabuSearch(Map* m)
{
	map = m;
	int count = m->getDimension();
	tabulist = vector<int*>(count);
	for(int i = 0; i < count; i++)
	{
		tabulist[i] = new int[count];
		for(int j = 0; j < count; j++)
		{
			tabulist[i][j] = 0;
		}
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
void TabuSearch::swap(int i1, int i2, tour* t)
{
	int left1 = i1-1;
	int right1 = i1+1;
	int left2 = i2-1;
	int right2 = i2+1;

	int lastIndex = map->getDimension()-1;
	

	// First remove old costs.
//	cout << "Cost is " << t->cost << endl;

	if(i1 == lastIndex)
	{
		t->cost -= map->getDistance(t->path[left1], t->path[i1]);	
		t->cost -= map->getDistance(t->path[0], t->path[i1]);
		t->cost -= map->getDistance(t->path[left2], t->path[i2]);
		t->cost -= map->getDistance(t->path[right2], t->path[i2]);
	}
	else if( i2 == lastIndex)
	{
		t->cost -= map->getDistance(t->path[left1], t->path[i1]);	
		t->cost -= map->getDistance(t->path[right1], t->path[i1]);
		t->cost -= map->getDistance(t->path[left2], t->path[i2]);
		t->cost -= map->getDistance(t->path[0], t->path[i2]);
	}
	else
	{
		t->cost -= map->getDistance(t->path[left1], t->path[i1]);	
		t->cost -= map->getDistance(t->path[right1], t->path[i1]);
		t->cost -= map->getDistance(t->path[left2], t->path[i2]);
		t->cost -= map->getDistance(t->path[right2], t->path[i2]);
	}

//	cout << "Cost after reduce is " << t->cost << endl;
	// Do switch
    int tmp = t->path[i1];
    t->path[i1] = t->path[i2];
    t->path[i2] = tmp;

    // Now recalculate costs
    if(i1 == lastIndex)
	{ 
		t->cost += map->getDistance(t->path[left1], t->path[i1]);
		t->cost += map->getDistance(t->path[0], t->path[i1]);
		t->cost += map->getDistance(t->path[left2], t->path[i2]);
		t->cost += map->getDistance(t->path[right2], t->path[i2]);
	}
	else if(i2 == lastIndex)
	{
		t->cost += map->getDistance(t->path[left1], t->path[i1]);
		t->cost += map->getDistance(t->path[right1], t->path[i1]);
		t->cost += map->getDistance(t->path[left2], t->path[i2]);
		t->cost += map->getDistance(t->path[0], t->path[i2]);
	}
	else
	{
		t->cost += map->getDistance(t->path[left1], t->path[i1]);
		t->cost += map->getDistance(t->path[right1], t->path[i1]);
		t->cost += map->getDistance(t->path[left2], t->path[i2]);
		t->cost += map->getDistance(t->path[right2], t->path[i2]);
	}

//	cout << "Recalculated cost is " << t->cost << endl;
//	cout << endl;
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
		//cout << "Index " << i << endl;
		for(int j = 1; j < count; j++)
		{
			if(i == j)
				continue;

			// Copy current best
			//tour* tourCandidate = new tour(vector<int>(count));
			/*for(int k = 0; k <count ; k++ )
			{
				tourCandidate->path[k] = bestTour->path[k];
			}
			swap(i, j, tourCandidate);*/
			if(tabulist[i][j] != 0)
				continue;

			double oldDistance = bestTour->cost;
			swap(i, j, bestTour);
			if(oldDistance > bestTour->cost)
			{
				firstNeighbour = false;
				city1 = i;
				city2 = j;

				#ifdef DEBUG_TRACE
					cout << bestTour->path[0];
					for(int i = 1; i < count; i++)
					{
						cout << " -> " << bestTour->path[i];
					}
					cout << "\n";
					cout << "COST: " << bestTour->cost << "\n";
				#endif
			}
			else
			{
				// Swap back as this was not a good switch
				swap(i, j, bestTour);
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

