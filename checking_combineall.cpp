/*Code which checks to see if the combineall functions work*/
#include <iostream>
#include <vector>
#include <set>
#include "combineall.h"


void check_getnvl_works(){
	std::vector<std::vector<int> > acc{{1,1,1},{1,1,1},{1,1,1}};
	std::set<int> V_t{0,1,2};
	std::set<int> ll, nvl_out ;
	
	nvl_out = get_Nvl(acc, V_t, ll);
	std::cout << "nvl_out:" << std::endl;
	for (auto nn : nvl_out){
		std::cout << nn << std::endl;
	}
	// Now make ll with a 1 in it 
	ll = {1};
	acc[0][1] = -1;
	nvl_out = get_Nvl(acc, V_t, ll);
	std::cout << "nvl_out:" << std::endl;
	for (auto nn : nvl_out){
		std::cout << nn << std::endl;
	}
	}
void check_get_not_nvl_works(){
	std::vector<std::vector<int> > acc{{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
	std::set<int> V_t{0,1,2};
	std::set<int> ll{0,1,2};
	std::set<int> not_nvl ;
	
	not_nvl = get_not_Nvl(acc, V_t, ll);
	std::cout << "NOT nvl_out:" << std::endl;
	for (auto nn : not_nvl){
		std::cout << nn << std::endl;
	}
}

void check_combine_all(){
	std::vector<std::vector<int> > acc{{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
	std::set<int> V_t{0,1,2};
	std::set<int> ll;
	std::set<int> X;
	std::vector<std::set<int> > solution;
	
	solution = combine_all(acc, V_t, ll, X);
	if (solution.empty()){
		std::cout << "Miaoe!! " << std::endl;
	}
	else{
		std::cout << "bow!" << std::endl;
		for (auto n : solution){
			for (auto k : n){
			std::cout << k << " set element " << std::endl;
		}
		}
	}
}


void check_combine_all_full(){
	std::vector<std::vector<int> > acc;
	std::set<int> V_t{0,1,2,3,4,5};
	std::set<int> ll;
	std::set<int> X;
	std::vector<std::set<int> > solution;
	acc = {{ 0, 1, 0, 0,-1,-1}, 
		   { 1, 0, 1, 1, 0, 1},
		   {0, 1,  0,-1, 1,  0},
		   {0, 1, -1, 0,-1,  0},
		   {-1, 0, 1,-1, 0, 1},
		   {-1, 1, 0, 0, 1, 0}};
	
	solution = combine_all(acc, V_t, ll, X);
	if (solution.empty()){
		std::cout << "Miaoe!! " << std::endl;
	}
	else{
		std::cout << "bow!" << std::endl;
		for (auto n : solution){
			for (auto k : n){
			std::cout << k << " set element " << std::endl;
		}
		}
	}
}




int main(){
	check_getnvl_works();
	check_get_not_nvl_works();
	check_combine_all();
	check_combine_all_full();
	return 0;
}