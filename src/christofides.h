#ifndef CHRISTOFIDES
#define CHRISTOFIDES

#include <vector>
#include "map.h"
#include "types.h"

tour christofides(Map* map);

// Prims algoritm.
std::vector<coordinate> minSpanTree(Map* map);


#endif
