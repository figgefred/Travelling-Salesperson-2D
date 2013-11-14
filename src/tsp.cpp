#include <stdlib.h>
#include <stdio.h>
//#include <sys/time.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

#define PRINT

typedef struct coordinate
{
	double x;
	double y;

	coordinate(double x1, double y1)
	{
		x = x1;
		y = y1;
	}
};

double** distance_mat;
coordinate** cities;
int count = 0;

void print_usage(string);
void initFromFile(string);
void initFromSTDin();
coordinate* getCoordinate(string);
double getDistance(coordinate*, coordinate*);
void initDistanceMatrix();

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		initFromSTDin();
	}
	else
	{
		initFromFile(argv[1]);
	}

	initDistanceMatrix();

	#ifdef PRINT
		cout << "\n\nCITIES \n";
		for(int i = 0; i < count; i++)
		{
			cout << "[" << i << "]: (" << cities[i]->x << ", " << cities[i]->y << ") \n";
		}

	#endif

	#ifdef PRINT
		cout << "\n\nDISTANCE MATRIX \n";
		for(int i = 0; i < count; i++)
		{
			for(int j = 0; j < count; j++)
			{
				printf("%i ", distance_mat[i][j]);
			}
			cout << "\n";
		}
	#endif


		// Free resources
	delete cities;
	delete distance_mat;

}

void initDistanceMatrix()
{
	
	distance_mat = new double*[count];
	for(int i = 0; i < count; i++)
	{
		distance_mat[i] = new double[count];
	}

	for(int i = 0; i < count; i++)
	{
		for(int j = 0; j < count; j++)
		{
			if(i == j)
				continue;

			if(distance_mat[i][j] != 0)
				continue;

			double dist = getDistance(cities[i], cities[j]);
			distance_mat[i][j] = dist;
			cout << "Calculated dist to " << dist<< "\n";
			cout << "Calculated m[i][j] to " << distance_mat[i][j]<< "\n";
			distance_mat[j][i] = dist;
		}
	}
}

double getDistance(coordinate* c1, coordinate* c2)
{
	double x = c1->x - c2->x;
	double y = c1->y - c2->y;
	
	double d = sqrt(pow(x, 2.0) + pow(y, 2.0));
	cout << "Calculated d to " << d<< "\n";
	return d;
}

void initFromSTDin()
{
	string line;
	getline(cin, line);
	count = atoi(line.c_str());

	cities = new coordinate*[count];

	for(int i = 0;i < count; i++)
	{

		getline(cin, line);
		cities[i] = getCoordinate(line);
	}
}


coordinate* getCoordinate(string s)
{
    string buf; 			// Have a buffer string
    stringstream ss(s); 	// Insert the string into a stream

    string tmp[2];  // Create vector to hold our words

    ss >> tmp[0];
    ss >> tmp[1];

    // close string stream?

    return new coordinate(atof(tmp[0].c_str()), atof(tmp[1].c_str()));
}


void initFromFile(string filename)
{
	return;
}

void print_usage(string output)
{
	string s = "USAGE: " + output + " <inputfile> ";
	cout << s;
}
