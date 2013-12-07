
#ifndef _TYPES

#include <string>
#include <vector>
#include <iostream>



#define _TYPES
struct coordinate {
	
	double x;
	double y;

	coordinate (double x1, double y1) {
		x = x1;
		y = y1;
	}
};

struct tour {
	double cost;
	std::vector<int> path;	

	tour(std::vector<int> p) {
		path = p;				
		cost = 0.0;
	}
	
	tour() {
		cost = 0.0;
	}

	~tour() {
		//delete path;
	}
};

coordinate* newCoordinate(std::string);
void printTour(tour*);

#endif

