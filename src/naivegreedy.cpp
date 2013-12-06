#include "naivegreedy.h"
#include "map.h"
#include <vector>

using namespace std;

// Kattis naive algorithm: https://kth.kattis.scrool.se/problems/oldkattis:tsp
tour* NaiveGreedy::naiveTspPath(Map* map)
{
	int N = map->getDimension();
	bool used[N];
	vector<int> path;
	// Init array
	for(int i = 0; i < N; i++)
	{
		used[i] = false;
		path.push_back(0);
	}
	used[0] = true;
	path[0] = 0;	
	//~ double totalcost = 0.0;
	
	for(int i = 1; i < N; i++)
	{
		int best = -1;
		double cost = 2147483647;
		
		for(int j = 0; j < N; j++)
		{
			if(used[j] || path[i-1] == j)
				continue;
			
			double d = map->getDistance(path[i-1], j);
			
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
		path[i] = best;
		used[best] = true;
	}
	
	return new tour(path);
}
