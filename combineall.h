/*

*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
/*based on  https://www.codespeedy.com/find-index-position-of-element-in-vector-in-c/*/

/*
std::vector<std::vector<int> > combine_all(std::vector<std::vector<int> > &Acc, std::vector<int> V, std::vector<int> l){
	std::vector<int> Nvl, N_not_vl;
	std::vector<std::vector<int> > solutions_l;
	N_vl = get_Nvl(Acc, V, l);
	N_not_vl = get_NOT_Nvl(Acc, V, l);
	
	if (N_vl.empty()){
		solutions_l.push_back(l);
	}
	else{
		
	}
	
	
}


*/



int searchResult(std::vector<int> in_v, int k){
	int index;
	std::vector <int> :: iterator itr;
	itr = std::find(in_v.begin(), in_v.end(), k);
	if (itr != in_v.end()){
	
	index =  std::distance (in_v.begin (), itr);
	}
	else{
	index = -1;
	}
	return index;
}

/**
  Mimics the behaviour of get_nvl written in Python. 

  @param Acc  The Compatibility-Conflict graph. 
  @param V_t  The set of vertices available, (V tilde). 
  @param l    The current solution set.
  @return Nvl Compatible solution set. 
  **/
std::vector<int> get_Nvl(std::vector<std::vector<int> > &Acc, std::vector<int> V_t, std::vector<int> l){
		int index;
		std::vector<int> Nvl;
		if (l.empty()==true){
			Nvl = V_t;}
		else{
			for (int v : V_t){
				for (int u : l){
					if (Acc[v][u]==1){
						Nvl.push_back(v);
					}
					else if(Acc[v][u]==-1){
						/*find where v is in Nvl*/
						index = searchResult(Nvl, v);
						/*and eliminate it from Nvl*/
						Nvl.erase(Nvl.begin()+index);
					}
				}
			}
			
			}
	return Nvl;

}

std::vector<int> get_not_Nvl(std::vector<std::vector<int> > &Acc, std::vector<int> V_t, std::vector<int> l){
		int index;
		std::vector<int> N_not_vl;
		if (l.empty()==true){
			return N_not_vl;}
		else{
			for (int v : V_t){
				for (int u : l){
					if (Acc[v][u] == -1){
						N_not_vl.push_back(v);
					}
					else if(Acc[v][u] == 1){
						/*find where v is in Nvl*/
						index = searchResult(N_not_vl, v);
						/*and eliminate it from Nvl*/
						N_not_vl.erase(N_not_vl.begin()+index);
					}
				}
			}
			
			}
	return N_not_vl;
}
	