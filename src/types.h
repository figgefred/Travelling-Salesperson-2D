
#ifndef _TYPES

#include <string>
#include <vector>

#define _TYPES
struct coordinate {
	
	double x;
	double y;

	coordinate (int x1, int y1) {
		x = x1;
		y = y1;
	}
};

struct tour {

	double cost;
	std::vector<int> path;
	tour(std::vector<int> p, double c) {
		path = p;
		cost = c;
	}
	~tour() {
		//delete path;
	}
};

coordinate* newCoordinate(std::string);

#endif

