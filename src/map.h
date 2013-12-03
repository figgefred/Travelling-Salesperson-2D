
#ifndef _MAP
#include <vector>
#include "types.h"

class Map
{
		double** distance_mat;
		std::vector<coordinate*> cities;
		int dim;

		double calculateDistance(coordinate*, coordinate*);
		void setDistanceMatrix();
	public:
		Map (std::vector<coordinate*>);
		~Map();
		std::vector<coordinate*> getCities();
		int getDimension();
		double getDistance(int, int);
		coordinate* getCityCoordinate(int);
		void setTourDistance(tour*);
		double getTourDistance(std::vector<int>*);
		double getTourDistance(tour* t);


};

#define _MAP
#endif
