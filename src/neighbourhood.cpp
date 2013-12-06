
#include <iostream>
#include <vector>
#include <algorithm>
#include "neighbourhood.h"

using namespace std;

// Private



// Public

Neighbourhood::Neighbourhood(int cIndex, int numCities, int maxNeighbours, double* ds)
{
	cityIndex = cIndex;
	distances = ds;
	vector<int> neighbourCandidates(numCities-1, numCities-1);
	int candidate = 0;
	for(int i = 0; i < numCities; i++)
	{
		if(cityIndex == candidate)
		{
			// Skip
			candidate++;
		}
		neighbourCandidates[i] = candidate;
		candidate++;
	}

	// Now lets sort
	sort(neighbourCandidates.begin(), neighbourCandidates.end(),
		[&](int const & a, int const & b) -> bool 
		// Return true if i is closer to j
		// Else false
		{return distances[a] < distances[b];});
	neighbours = vector<int>(maxNeighbours, maxNeighbours);
	for(int i = 0; i < maxNeighbours; i++)
	{
		neighbours[i] = neighbourCandidates[i];
		neighbourSet.insert(neighbours[i]);
	}
}

Neighbourhood::~Neighbourhood()
{}

int Neighbourhood::getNeighbour(int i)
{
	return neighbours[i];
}

bool Neighbourhood::containsNeighbour(int candidate)
{
	return neighbourSet.find(candidate) != neighbourSet.end();
}

int Neighbourhood::getLastIndex()
{
	return neighbours.size()-1;
}

int Neighbourhood::getNeighbourCount()
{
	return neighbours.size();
}

void Neighbourhood::printNeighbours()
{
	cout << "Top " << getNeighbourCount() << " closest neighbours for city " << cityIndex << endl;
	for(int i = 0; i < getNeighbourCount(); i++)
	{
		cout << neighbours[i] << " " << endl;
	}
	cout << endl;
}