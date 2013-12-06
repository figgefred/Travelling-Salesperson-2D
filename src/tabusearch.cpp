
//#include <math.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <unordered_set>

#include "types.h"
#include "map.h"
#include "tabusearch.h"

#include <ctime>

using namespace std;

TabuSearch::TabuSearch(Map* m)
{
	map = m;
	//int count = m->getDimension();
	//tabulist;
	/*for(int i = 0; i < count; i++)
	{
		tabulist[i] = new int[count];
		for(int j = 0; j < count; j++)
		{
			tabulist[i][j] = 0;
		}
	}*/
}

TabuSearch::~TabuSearch()
{

}

// Private

//swaps two cities
void TabuSearch::swap(vector<int>* t, int i1, int i2)
{
	// Do switch
    int tmp = (*t)[i1];
    (*t)[i1] = (*t)[i2];
    (*t)[i2] = tmp;
}

double TabuSearch::getNewCost(vector<int>* t, int i1, int i2) {
	int city1 = (*t)[i1];
	int city2 = (*t)[i2];
	
	int lastIndex = (*t).size()-1;	
	//~ cout << lastIndex << endl;
	int left1 = (*t)[i1-1];
	int right1 = i1 < lastIndex ? (*t)[i1+1] : (*t)[0];
	int left2 = (*t)[i2-1];
	int right2 = i2 < lastIndex ? (*t)[i2+1] : (*t)[0];
	
 
	double cost = 0;	
	
	cost -= map->getDistance(city1, left1);		
	cost -= map->getDistance(city2, right2);	
	cost += map->getDistance(city2, left1);	
	cost += map->getDistance(city1, right2);
	
	if(right1 == city2) {
		//~ cout << i1 << " " << i2 << endl;
		return cost;
	}
	
	cost -= map->getDistance(city1, right1);
	cost -= map->getDistance(city2, left2);	
	cost += map->getDistance(city1, left2);
	cost += map->getDistance(city2, right1);
	
	return cost;
}

// Public

tour* TabuSearch::getBetterTour(tour* t)
{	
	std::clock_t start = std::clock();   
	t->cost = map->getTourDistance(t);	
	int max = 100;
	int counter = 0;
	bool timeout = false;
	do
	{
		timeout = (( std::clock() - start ) / (double) CLOCKS_PER_SEC) > 1.7;
		counter++;
		tour* newTour = findNewTour(t);
		if(newTour == NULL)
		{
		//	continue;
			break;
		}
		delete t;
		t = newTour;
		tabulist.clear();
	} while(!timeout);
	//cout << "Ran " << counter << " rounds!" << endl;
	//while( && i < max){
	return t;	
}

tour* TabuSearch::findNewTour(tour* curr_tour)
{
	// Tour size
	int count = curr_tour->path.size();
	vector<int> tmpTour(count, count);
	for(int i = 0; i < count; i++)
	{
		tmpTour[i] = curr_tour->path[i];
	}
//	tour* t = new tour(tmpTour);
	double tour_cost = curr_tour->cost;

	// Some initial values
	int cIndex1 = -1;
	int cIndex2 = -1;
	//double bestCostDiff = 0;
	bool changed = false;

	for(int i = 1; i < count; i++)
	{
		//cout << "Index " << i << endl;
		Neighbourhood* neighbourhood = map->getNeighbourhood(tmpTour[i]);
		for(int j = i; j < count; j++)//int j = 0; j < neighbourhood->getNeighbourCount(); j++)
		{
			int candidate = tmpTour[j];
			if(!neighbourhood->containsNeighbour(candidate))
			{
				continue;
			}

			if(tabulist.find(candidate) != tabulist.end() || i == j)
			{
				continue;
			}
			double cDiff = getNewCost(&tmpTour, i, j);
			if(cDiff < 0)//bestCostDiff)
			{
				//firstNeighbour = false;
				//cIndex1 = i;
				//cIndex2 = j;
				changed = true;
				tabulist.insert(candidate);
				//tabulist.insert(t->path[i]);
				swap(&tmpTour, i, j);
				tour_cost += cDiff;
			}	
		}
		/*if(tabulist.size() > 10)
		{
			tabulist.clear();
		}*/
	}

	if(!changed)//cIndex1 == -1)
		return NULL;
	//cout << "Wohoooooo lets switch cIndex1=" << cIndex1 << " with cIndex2=" << cIndex2 << endl;
	//tabulist[cIndex1][cIndex2]++;
	//tabulist[cIndex2][cIndex1]++;
	tour* t = new tour(tmpTour);
	t->cost = tour_cost;
	return t;
}

void TabuSearch::reset()
{

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

