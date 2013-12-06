#include "types.h"
#include <string>
#include <sstream>
#include <iostream>

#define KATTIS

using namespace std;

coordinate* newCoordinate(string s)
{
    string buf; 			// Have a buffer string
    stringstream ss(s); 	// Insert the string into a stream

    string tmp[2];  // Create vector to hold our words

    ss >> tmp[0];
    ss >> tmp[1];

    // close string stream?

    return new coordinate(atof(tmp[0].c_str()), atof(tmp[1].c_str()));
}

void printTour(tour* t)
{
	int count = t->path.size();
	#ifdef KATTIS
		for(int i = 0; i < count; i++)
		{
			cout << t->path[i] << "\n";
		}
		cout << "\n";
	#else
		cout << t->path[0];
		for(int i = 1; i < count; i++)
		{
			cout << " -> " << t->path[i];
		}
		cout << "\n";
		cout << "COST: " << t->cost << "\n";
	#endif
}
