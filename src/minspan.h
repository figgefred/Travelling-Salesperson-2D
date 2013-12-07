#ifndef MINSPAN
#define MINSPAN

#include <vector>
#include "map.h"
#include "types.h"
#include <unordered_set>

// http://www.win.tue.nl/~mdberg/Onderwijs/AdvAlg_Material/Course%20Notes/lecture8.pdf

struct edge {
	int x;
	int y;
	double cost;
};

tour* approxTSP(Map* map);
void innerTraversal(tour* t, std::vector<coordinate>* tree, std::unordered_set<int>* visited, int currentnode);

// Prims algoritm.
std::vector<edge*>* minSpanTree(Map* map);

bool edge_comparator (edge* i,edge* j);



#endif
