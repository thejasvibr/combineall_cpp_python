/*Code which checks to see if the combineall functions work*/
#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include "combineall.h"
//#include "rapidcsv.h" //external library from https://github.com/d99kris/rapidcsv

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
	std::vector<std::vector<int> > acc;
	acc = {{ 0, 1, 0, 0,-1,-1}, 
		   { 1, 0, 1, 1, 0, 1},
		   {0, 1,  0,-1, 1,  0},
		   {0, 1, -1, 0,-1,  0},
		   {-1, 0, 1,-1, 0, 1},
		   {-1, 1, 0, 0, 1, 0}};
	std::set<int> V_t{0,1,2,3,4,5};
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

void check_combine_all_full(int runs){
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
	for (int i=0; i<runs; i++){
		solution = combine_all(acc, V_t, ll, X);
	}
}


void check_combine_all_big(int runs){
	std::vector<std::vector<int> > acc;
	std::set<int> V_t;
	std::set<int> ll;
	std::set<int> X;
	std::vector<std::set<int> > solution;
	int num_rows;
	
	
	acc = {{  0, -1,  1, -1, -1,  1,  0,  0,  0,  1,  1, -1}, 
		   {-1,  0, -1,  0,  0,  1,  1,  1,  1, -1,  1,  1},
		   { 1, -1,  0, -1,  1, -1,  1,  0,  0, -1,  1,  0},
		   {-1,  0, -1,  0,  1,  0,  0,  1,  1,  0,  0,  1},
		   {-1,  0,  1,  1,  0, -1, -1, -1,  1,  1,  0,  0},
		   {1,  1, -1,  0, -1,  0,  1, -1,  0,  0,  1,  0},
		   { 0,  1,  1,  0, -1,  1,  0,  0,  1,  0, -1, -1},
		   { 0,  1,  0,  1, -1, -1,  0,  0,  0, -1, -1, -1},
		   { 0,  1,  0,  1,  1,  0,  1,  0,  0,  1,  1, -1},
		   { 1, -1, -1,  0,  1,  0,  0, -1,  1,  0,  1, -1},
		   { 1,  1,  1,  0,  0,  1, -1, -1,  1,  1,  0, -1},
		   {-1,  1,  0,  1,  0,  0, -1, -1, -1, -1, -1,  0}};
	V_t =  {0,1,2,3,4,5,6,7,8,9,10,11};
	for (int i=0; i<runs; i++){
		solution = combine_all(acc, V_t, ll, X);
	}
}


int main(){
	int runs = 10000;
	
	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::microseconds;
	
	check_getnvl_works();
	check_get_not_nvl_works();
	check_combine_all();
	std::cout << "Big matrix run" << std::endl;
	auto t1 = high_resolution_clock::now();
	check_combine_all_big(10);
	auto t2 = high_resolution_clock::now();
	auto ms_int = duration_cast<microseconds>(t2 - t1);
	auto timediff = duration_cast<microseconds>(t2-t1);
	std::cout << timediff.count()/(double)10 << "microseconds for 10 run";
	std::cout << "Big matrix run end ..." << std::endl;
	double per_run ;
	
	

	std::cout << "starting run" << std::endl;
    t1 = high_resolution_clock::now();
	check_combine_all_full(runs);
    t2 = high_resolution_clock::now();

    /* Getting number of nanos as an integer. */
    ms_int = duration_cast<microseconds>(t2 - t1);
	
    /* Getting number of nanos as a double. */
    duration<double, std::micro> ms_double = t2 - t1;

    std::cout << ms_int.count() << " micro sec\n";
    std::cout << ms_double.count() << " micro sec\n";
	per_run = ms_double.count()/1e6/((double)runs);
	std::cout << per_run << " seconds per run..";
	std::cout << "end run" << std::endl;
	
	return 0;
}