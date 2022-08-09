/*

*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include "sets_tryingout.cpp"

/**
  Mimics the behaviour of get_nvl written in Python. 

  @param Acc  The Compatibility-Conflict graph. 
  @param V_t  The set of vertices available, (V tilde). 
  @param l    The current solution set.
  @return Nvl Compatible solution set. 
  **/
std::set<int> get_Nvl(std::vector<std::vector<int> > &Acc, std::set<int> V_t, std::set<int> l){
		int index;
		std::set<int> Nvl;
		if (l.empty()==true){
			for (auto ii : V_t){
				Nvl.insert(ii);
				}
		}
		else{
			for (int v : V_t){
				for (int u : l){
					if (Acc[v][u]==1){
						Nvl.insert(v);
					}
					else if(Acc[v][u]==-1){
						/*find where v is in Nvl
						index = searchResult(Nvl, v);
						and eliminate it from Nvl
						Nvl.erase(Nvl.begin()+index);*/
						Nvl.erase(v);
					}
				}
			}
			
			}
	return Nvl;

}

std::set<int> get_not_Nvl(std::vector<std::vector<int> > &Acc, std::set<int> V_t, std::set<int> l){
		//int index;
		std::set<int> N_not_vl;
		if (l.empty()==true){
			return N_not_vl;}
		else{
			for (int v : V_t){
				for (int u : l){
					if (Acc[v][u] == -1){
						N_not_vl.insert(v);
					}
					else if(Acc[v][u] == 1){
						/*find where v is in Nvl
						index = searchResult(N_not_vl, v);*/
						/*and eliminate it from Nvl*/
						N_not_vl.erase(v);
					}
				}
			}
			
			}
	return N_not_vl;
}

std::vector<std::set<int> > combine_all(std::vector<std::vector<int> > &Acc, std::set<int> V, std::set<int> l, std::set<int> X){
	std::set<int> Nvl, N_not_vl;
	std::vector<std::set<int> > solutions_l;
	std::set<int> Nvl_wo_X, Vx;
	std::set<int> temp_set, lx;
	std::vector<std::set<int> > current_solution;

	Nvl = get_Nvl(Acc, V, l);
	N_not_vl = get_not_Nvl(Acc, V, l);
	
	if (Nvl.empty()){
		solutions_l.push_back(l);
	}
	else{
		// remove conflicting nodes
		V = diff_set(V, N_not_vl);
		// unvisited compatible neighbours
		Nvl_wo_X = diff_set(Nvl, X);
		for (int n : Nvl_wo_X){
			temp_set = {n};
			Vx = diff_set(V, temp_set);
			lx = union_set(l, temp_set);
			for (auto k : Vx){
				std::cout << "Vx components " << k << std::endl;
				} 
			current_solution = combine_all(Acc, Vx, lx, X);
			if (!current_solution.empty()){
				for (auto each : current_solution){
					solutions_l.push_back(each);
				}
			
			}
			X.insert(n);
		}
	}
	return solutions_l;
}
