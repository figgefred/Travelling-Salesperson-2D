
#ifndef _MAP
#include <vector>
#include "types.h"

class Map
{
		double** distance_mat;		
		int dim;
		double calculateDistance(coordinate*, coordinate*);
		void setDistanceMatrix(std::vector<coordinate*>* cities);
		
		
	public:
		Map (std::vector<coordinate*>*);
		~Map();
		std::vector<int>* getNeighbourhood(int cityID);
		int getDimension();
		double getDistance(int, int);
		//~ coordinate* getCityCoordinate(int);
		double getTourDistance(std::vector<int>&);
		double getTourDistance(tour* t);


};

#define _MAP
#endif
