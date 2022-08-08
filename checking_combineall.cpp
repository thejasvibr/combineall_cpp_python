/*Code which checks to see if the combineall functions work*/
#include <iostream>
#include <vector>
#include "combineall.h"


void check_getnvl_works(){
	std::vector<std::vector<int> > acc{{1,1,1},{1,1,1},{1,1,1}};
	std::vector<int> V_t{0,1,2};
	std::vector<int> ll, nvl_out ;
	
	nvl_out = get_Nvl(acc, V_t, ll);
	std::cout << "nvl_out:" << std::endl;
	for (auto nn : nvl_out){
		std::cout << nn << std::endl;
	}
	}

int main(){
	check_getnvl_works();
	
	return 0;
}