#ifndef ADV_TYPES_H
#define ADV_TYPES_H

#include <vector>
#include "base_types.h"
#include <string>

/**
  *	\struct triple
  *	\brief Data structure for storage of a subgraph with 3 vertices.
  */
struct triple{
    int es[3];
    double w[3];
    int widx[3];
    int ns[3];
    int tridx;
    bool used;
};
typedef std::vector<triple*> t_v;
typedef t_v::const_iterator t_it;

/**
  *	\struct graph
  *	\brief Data structure for storage of a subgraph/complete graph with more than 3 vertices.
  */
struct graph{
    i_v widx, tridx, qidx;
    b_v valid;
    bool used;
};
typedef std::vector<graph*> g_v;
typedef g_v::const_iterator g_it;

/**
  *	\struct loop
  *	\brief Data structure for storage of the vertices and weight information of a loop.
  */
struct loop{
    d_v w;
    b_v v;
    i_v widx;
    bool used;
    int loop_number;
};
typedef std::vector<loop*> l_v;
typedef l_v::const_iterator l_it;

/**
  *	\struct loopset
  *	\brief Data structure for storage of a set of loop structs.
  */
struct loopset{
    i_v edges, dir;
    l_v loops;
};
typedef std::vector<loopset*> ls_v;
typedef ls_v::const_iterator ls_it;

/**
  *	\struct conf
  *	\brief Data structure for storage of the setup information of a simulation.
  */
struct conf{
    double eps;
    int norm, st, n0, alg, nl,  additionaltree;
    char *input;
    std::string inn;
    char *output;
    std::string out;
};
typedef std::vector<conf*> c_v;
typedef c_v::const_iterator c_it;

/**
  *	\struct
  *	\brief Data structure for storage of the preprocessing sorting parameters
  */


#endif // ADV_TYPES_H
