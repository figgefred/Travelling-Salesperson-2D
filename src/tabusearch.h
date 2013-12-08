
#ifndef _TABUSEARCH
#include "localsearch.h"
#include "types.h"
#include <vector>
#include <unordered_set>
#include <list>
#include <ctime>

struct city_edge {
	int c1;
	int c2;

	city_edge(int city1, int city2)
	{
		c1 = city1;
		c2 = city2;
	}

    bool operator == ( const city_edge& e ) const
    {
        return ( ( c1 == e.c1 ) && ( c2 == e.c2 ) ) || ( ( c1 == e.c2 ) && ( c2 == e.c1 ) );
    }

};

struct edgehash
{
    std::size_t operator () ( const city_edge& e ) const
    {

 		// Lets hope the cast still allows us to avoid hash collisions
        return e.c1 * e.c2;
    }
};

class TabuSearch : public LocalSearch
{
	private:
		int tabu_dim;
		int** tabu_record;
		//std::unordered_set<edge, edgehash> tabu_list;
		std::list<city_edge> tabu_list;
		//std::vector<int> tabu_count;
		
		tour* flip(tour*, int, int );
		tour* swap(tour* t, int from, int to, double cost);
		double getNewCost(tour*, int, int);
		bool findNewTour(tour*);
		
		inline bool isTabu(int, int);
		void tabu_move(int, int);
		void expire_move();
		void expire_move(int, int);
		void clear_tabu();

	public:
		TabuSearch(Map*);
		virtual ~TabuSearch();
		virtual tour* getBetterTour(tour*, std::clock_t);
};

#define _TABUSEARCH
#endif
