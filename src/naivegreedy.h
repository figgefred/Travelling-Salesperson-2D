#ifndef _naivegreedy
#define _naivegreedy
#include "types.h"
#include "map.h"

class NaiveGreedy {	
	
	public:
		tour* naiveTspPath(Map* map);
		tour* naiveTspPath(Map* map, int startnode);
	
};


#endif
