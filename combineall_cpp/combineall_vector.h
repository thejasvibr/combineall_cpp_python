/*
Vector version of TB's combineall
=================================
CombineAll is a routine which solves a 'compatibility' problem.
Essentially there are multiple vertices in a graph that are either compatible
or not with each other. CombineAll finds all possible combinations of 
vertices that are compatible with each other. The compatibility/conflict between
vertices is represented as a 2D matrix with +1 for compatibility and -1 for 
conflict (and 0's to indicate NAs). 

Another change is that the Nvl and N_not_vl are calculated together - thus removing the 
need to loop and find indices etc. 


Reference
---------
* Kreissig & Yang 2013, Fast and reliable TDOA assignment in multi-source reverberant environments, ICASSP 2013
  https://ieeexplore.ieee.org/abstract/document/6637668?casa_token=3oKOQUJRuWQAAAAA:JNbwI-gf0m0ozfAKbAQJzblq8qE-NPTJ49hgJILMxG_2ZM9MJOt4PQOvPEQn9TXJZSzD_ON6YA
*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include "set_operations.h" // diff_set and union_set set operations defined here

struct nvl_notnvl 
{
	std::vector<int> Nvl;
	std::vector<int> notNnvl;
};


/*
The common Nvl and notNvl implementation inspired by Martin Kreissig's code.
*/
auto get_Nvl_and_notNvl(const std::vector<std::vector<int> > &acc, const std::vector<int>& V, const std::vector<int>& l){
	bool compatible, conflict;
	nvl_notnvl results;

	if (l.empty()){
		for (auto jj :V){results.Nvl.push_back(jj);}
	}
	else {
		for (auto v : V){
			 compatible = false;
			 conflict = false;
			for (auto u: l){
				if (acc[v][u] == -1){
					conflict=true;
					}
				else if (acc[v][u] == 1){
					compatible=true;
					}
			}
			if (conflict){
				results.notNnvl.push_back(v);
						}
			else if(compatible){
				results.Nvl.push_back(v);
					}
		}
	
	}	
	return results;
}

void vect_print(std::vector<int> XX){
	for (auto x : XX){
	std::cout << x << ",";
	}
	std::cout << std::endl;
}

/**
  Finds multiple compatible solutions where nodes don't conflict each other.

  @param Acc  The Compatibility-Conflict graph. 
  @param V_t  The set of vertices available 
  @param l    The current solution set.
  @param X    Already visited vertices.
  @solutions_l All possible vertex combinations that are compatible with each other.
  **/


std::vector<std::vector<int>> combine_all(const std::vector<std::vector<int> > &Acc, std::vector<int> V, const std::vector<int>& l, std::vector<int> X){
	std::vector<std::vector<int> > solutions_l;
	std::vector<int> Nvl_wo_X, Vx;
	std::vector<int> temp_set, lx;
	std::vector<std::vector<int> > current_solution;
	nvl_notnvl nodes_in_play;
	
	nodes_in_play = get_Nvl_and_notNvl(Acc, V, l); // holds Nvl and notNvl
	
	if (nodes_in_play.Nvl.empty()){
		solutions_l.push_back(l);
	}
	else{
		// remove conflicting nodes
		V = diff_set_vect(V, nodes_in_play.notNnvl);
		// unvisited compatible neighbours
		Nvl_wo_X = diff_set_vect(nodes_in_play.Nvl, X);
		for (int n : Nvl_wo_X){
			temp_set = {n};
			Vx = diff_set_vect(V, temp_set);
			lx = union_set_vect(l, temp_set);
			current_solution = combine_all(Acc, Vx, lx, X);
			if (!current_solution.empty()){
				for (auto each : current_solution){
					solutions_l.push_back(each);
				}

			}
			// build onto set of visited neighbours
			X.push_back(n);
		}
	}
	return solutions_l;
}

void check_ky2013_eg(){
	std::vector<std::vector<int> > acc;
	acc = {{ 0, 1, 0, 0,-1,-1}, 
		   { 1, 0, 1, 1, 0, 1},
		   {0, 1,  0,-1, 1,  0},
		   {0, 1, -1, 0,-1,  0},
		   {-1, 0, 1,-1, 0, 1},
		   {-1, 1, 0, 0, 1, 0}};
	std::vector<int> V_t{0,1,2,3,4,5};
	std::vector<int> ll;
	std::vector<int> X;
	std::vector<std::vector<int> > solution;
	
	solution = combine_all(acc, V_t, ll, X);
	if (solution.empty()){
		std::cout << "Miaoe!! " << std::endl;
	}
	else{
		std::cout << "bow!" << std::endl;
		for (auto n : solution){
			for (auto k : n){
			std::cout << k << ",";
		}
		std::cout << " " <<std::endl;
		}
	}
	
}

/*int main(){
	std::vector<int> yy;
	std::vector<int> aa = {1,2,3};
	std::vector<int> bb = {9,10,11};
	std::cout << "diff between aa and bb is :" << std::endl;
	yy = diff_set_vect(aa,bb);
	for (auto j : yy)
	{
		std::cout << "Element diff:" << j << std::endl;
	}
	
	std::cout << "\n Unionset example" << std::endl;
	std::vector<int> miaow = union_set_vect(aa,bb);
	for(auto i : miaow){
		std::cout << i << ",";
	}
	std::cout << " " << std::endl;
	
	
	// Now test out the CCG case:
	check_ky2013_eg();
	
	return 0;
	
}*/