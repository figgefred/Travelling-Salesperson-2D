#include "naivegreedy.h"
#include "map.h"

// Kattis naive algorithm: https://kth.kattis.scrool.se/problems/oldkattis:tsp
tour* NaiveGreedy::naiveTspPath(Map* map)
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
	double totalcost = 0.0;
	
	for(int i = 1; i < N; i++)
	{
		int best = -1;
		double cost = 2147483647;
		
		for(int j = 0; j < N; j++)
		{
			if(used[j] || newTour->path[i-1] == j)
				continue;
			
			double d = map->getDistance(newTour->path[i-1], j);
			
			if(best == -1 || d < cost)
			{
				best = j;
				cost = d;
			}
		}
		#ifdef DEBUG_TRACE
			cout << "Best " << best << endl;
			cout << "Cost " << cost << endl;
		#endif
		newTour->path[i] = best;
		used[best] = true;
		totalcost += cost;
	}

	// Add last step back to origin
	totalcost += map->getDistance(newTour->path[N-1], newTour->path[0]);
	newTour->cost = totalcost;
	//exit(0);
	return newTour;
}
