
#ifndef _MAP
	#include <vector>
	#include "types.h"

	class Map
	{
		private:
			double** distance_mat;
			std::vector<coordinate*> cities;
			//std::vector<Neighbourhood*> closestNeighbours;
			int dim;
			double calculateDistance(coordinate*, coordinate*);
			void setDistanceMatrix();
			//void setLocalNeighbourhoods();
		public:
			Map (std::vector<coordinate*>);
			~Map();
			std::vector<coordinate*> getCities();
			int getDimension();
			double getDistance(int, int);
			coordinate* getCityCoordinate(int);
			void setTourDistance(tour*);
			double getTourDistance(std::vector<int>&);
			double getTourDistance(tour* t);
			//Neighbourhood* getNeighbourhood(int);
	};

	#define _MAP
#endif
