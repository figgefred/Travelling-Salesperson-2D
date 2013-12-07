
#ifndef _TABUSEARCH
#include "localsearch.h"
#include "types.h"
#include <vector>
#include <unordered_set>
#include <list>

/*struct edge {
	int c1;
	int c2;
	double distance;

	edge(int city1, int city2, double d)
	{
		c1 = city1;
		c2 = city2;
		distance = d;
	}

    bool operator == ( const edge& e ) const
    {
        return ( ( c1 == e.c1 ) && ( c2 == e.c2 ) ) || ( ( c1 == e.c2 ) && ( c2 == e.c1 ) );
    }

};

struct edgehash
{
    std::size_t operator () ( const edge& e ) const
    {

 		// Lets hope the cast still allows us to avoid hash collisions
        return e.c1 * e.c2 * ((int)e.distance);
    }
};*/

class TabuSearch : public LocalSearch
{
	private:
		int tabu_dim;
		int** tabu_record;
		//std::unordered_set<edge, edgehash> tabu_list;
		std::list<int> tabu_order;
		
		tour* flip(tour*, int, int );
		tour* swap(tour* t, int from, int to, double cost);
		double getNewCost(tour*, int, int);
		bool findNewTour(tour*);
		
		inline bool isTabu(int, int);
		std::pair<int, int> popTabu();
		void tabu_move(int, int);
		void expire_move();

	public:
		TabuSearch(Map*);
		virtual ~TabuSearch();
		virtual tour* getBetterTour(tour*);
};

#define _TABUSEARCH
#endif
