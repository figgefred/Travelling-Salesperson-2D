
#ifndef _NEIGHBOURHOOD
	#include <vector>
	#include "types.h"
	#include "unordered_set"

	class Neighbourhood {

		private:
			int cityIndex;
			std::vector<int> neighbours;
			std::unordered_set<int> neighbourSet;
			double* distances;

		public: 
			Neighbourhood(int, int, int, double[]);
			~Neighbourhood();
			bool containsNeighbour(int);
			int getNeighbour(int);
			int getLastIndex();
			int getNeighbourCount();
			void printNeighbours();

	};

	#define _NEIGHBOURHOOD
#endif