#include "minspan.h"

#include <vector>
#include <unordered_set>
#include <iostream>
#include <ctime>
#include <algorithm>    // std::sort

using namespace std;


bool edge_comparator (edge* i,edge* j) {
	 return (i->cost<j->cost); 
}

void innerTraversal(tour* t, vector<edge*>* tree, unordered_set<int>* visited, int currentnode) {
	if(visited->count(currentnode) > 0)
		return;
		
	//~ cout << "Now checking node:" << currentnode << endl;
	visited->insert(currentnode);
	t->path.push_back(currentnode);	
	for(unsigned int i = 0; i < tree->size(); ++i)
	{
		edge* e = tree->at(i); 
		if(e->x == currentnode) {
			//~ cout << currentnode << " found edge: " << e->x << " " << e->y << endl;
			innerTraversal(t, tree, visited, e->y);
			//~ cout << "Recursed out now at:" << currentnode << endl;			
		}
		else if(e->y == currentnode) {
			//~ cout << currentnode << " found edge: " << e->x << " " << e->y << endl;
			innerTraversal(t, tree, visited, e->x);
			//~ cout << "Recursed out now at:" << currentnode << endl;	
		}
	}
}


// http://en.wikipedia.org/wiki/Christofides_algorithm
tour* approxTSP(Map* map) {	
	//~ cout << std::clock() / (double) CLOCKS_PER_SEC << " s" << endl;
	vector<edge*>* tree = minSpanTree(map);
	//~ cout << std::clock() / (double) CLOCKS_PER_SEC << " s" << endl;

	tour* t = new tour();
	
	unordered_set<int>* visited = new unordered_set<int>;
	innerTraversal(t, tree, visited, 0);
	//~ cout << "Traversal done: " << std::clock() / (double) CLOCKS_PER_SEC << " s" << endl;
	//~ cout << "Path: " << t->path.size() << endl;
	//~ printTour(t);
	//~ cout << map->getTourDistance(t) << endl;
	
	return t;
}

// Kruskal
vector<edge*>* minSpanTree(Map* map) {
	
	vector<edge*>* edges = new vector<edge*>();	
	for(int i = 0; i < map->getDimension(); ++i)
	{
		for(int j = 0; j < map->getDimension(); ++j)
		{
			if(i == j)
				continue;
				
			edge* e = new edge();
			e->x = i;
			e->y = j;
			e->cost = map->getDistance(i,j);
			edges->push_back(e);
		}
	}
	
	
	sort(edges->begin(), edges->end(), edge_comparator);
	
	vector<edge*>* tree = new vector<edge*>();	
	vector<int> sets;
	for(int i = 0; i < map->getDimension(); ++i)
		sets.push_back(i);
	
	unordered_set<int>* uvals = new unordered_set<int>; 
	unordered_set<int>* vvals = new unordered_set<int>;
	
	for(int i = 0; i < edges->size(); ++i)
	{
		edge* e = edges->at(i);
		
		//
		if(sets[e->x] == sets[e->y]) {
			delete e;
			continue;					
		}
		
		tree->push_back(e);	
		int oldset = sets[e->y];
		for(int j = 0; j < sets.size(); j++)
			if(sets[j] == oldset)
				sets[j] = sets[e->x];		 
	}
	
	delete uvals;
	delete vvals;
	//~ for(int i = 0; i < edges->size(); i++)
		//~ delete edges->at(i);
		
	delete edges;
	
	return tree;
}
