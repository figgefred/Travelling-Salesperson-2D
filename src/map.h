
#ifndef _MAP
#include <vector>
#include "types.h"

class Map
{
		double** distance_mat;
		std::vector<coordinate*> cities;

		double calculateDistance(coordinate*, coordinate*);
		void setDistanceMatrix();
	public:
		Map (std::vector<coordinate*>);
		~Map();
		std::vector<coordinate*> getCities();
		int getCityCount();
		double getDistance(int, int);
		coordinate* getCityCoordinate(int);
		void setTourDistance(tour*);
		double getTourDistance(std::vector<int>*);


};

#define _MAP
#endif