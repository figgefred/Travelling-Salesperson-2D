#include "randomtour.h"
#include "map.h"
#include <vector>

using namespace std;

// Kattis naive algorithm: https://kth.kattis.scrool.se/problems/oldkattis:tsp
tour* RandomTour::randomTspPath(Map* map)
{
	int N = map->getDimension();
	//bool used[N];

	vector<int> indexes(N, N);
	indexes[0] = 0;
	for(int i = 1; i < N; i++)
	{
		indexes[i] = i;
	//	used[i] = false;
	}
	
	vector<int> tourPath(N, N);
	double totalcost = 0.0;

	// Set start position
	
	int start;
	{
		int sIndex = rand() % N;
		start = indexes[sIndex];
		indexes.erase(indexes.begin() + sIndex);
	}
	//used[start] = true;
	tourPath[0] = start;	
	int pos = 1;
	
	while(indexes.size() > 0)
	{
		int cIndex = rand() % indexes.size();
		tourPath[pos] = indexes[cIndex];
		indexes.erase(indexes.begin() + cIndex);
		totalcost += map->getDistance(tourPath[pos-1], tourPath[pos++]);
	} 
	// Add last step back to origin
	tour* newTour = new tour(tourPath);
	totalcost += map->getDistance(tourPath[N-1], start);
	
	// Set cost to struct
	newTour->cost = totalcost;
	return newTour;
}
