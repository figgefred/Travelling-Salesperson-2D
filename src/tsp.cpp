
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

#include "map.h"
#include "types.h"

using namespace std;

#define PRINT

//double** distance_mat;
Map* map;

void print_usage(string);
vector<coordinate*>* getCitiesFromSTDin();

int main(int argc, char* argv[])
{
	vector<coordinate*> cities = *(getCitiesFromSTDin());
	int count = cities.size();
	if(cities.size() == 0)
	{
		exit(0);
	}

	#ifdef PRINT
		cout << "\n\nCITIES \n";
		for(int i = 0; i < count; i++)
		{
			cout << "[" << i << "]: (" << cities[i]->x << ", " << cities[i]->y << ") \n";
		}
	#endif

	map = new Map(cities);

	#ifdef PRINT
		cout << "\n\nDISTANCE MATRIX \n";
		for(int i = 0; i < count; i++)
		{
			for(int j = 0; j < count; j++)
			{
				cout << map->getDistance(i, j) << " ";
			}
			cout << "\n";
		}
	#endif

	// Free resources
	delete map;

}

vector<coordinate*>* getCitiesFromSTDin()
{
	string line;
	getline(cin, line);
	int count = atoi(line.c_str());

	vector<coordinate*>* cities = new vector<coordinate*>();

	for(int i = 0;i < count; i++)
	{

		getline(cin, line);
		(*cities).push_back(newCoordinate(line));
	}

	return cities;
}


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

void print_usage(string output)
{
	string s = "USAGE: " + output + " <inputfile> ";
	cout << s;
}
