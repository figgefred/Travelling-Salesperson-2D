
#ifndef _TYPES

#include <string>

#define _TYPES
struct coordinate {
	
	double x;
	double y;

	coordinate (int x1, int y1) {
		x = x1;
		y = y1;
	}
};

coordinate* newCoordinate(std::string);

#endif

