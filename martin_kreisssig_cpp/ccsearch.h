/**
  *	\class cCCSearch
  *	\brief Class that creates the compatibility-conflict graph and finds
  *         all compatible combinations
  *
  *
  *	\author Martin Kreissig
  *	\date dec 2012
  *	\version 1.0
  */

#ifndef CBRONKERBMODK_H
#define CBRONKERBMODK_H

#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include "adv_types.h"


class cCCSearch
{
public:
    cCCSearch( void );
    i_m findCCIS(i_m AdjMm );
	i_m solution_set;  // compatible solutions set

private:
    int M;  // number of cc-graph vertices
    
    void full_search(i_m AdjM, i_v vertices, i_v solution, i_v visited_vertices );
};

#endif // CBRONKERBMODK_H
