/*Checks to see if the combineall functions work, 
and implements the 'known' + 'large' matrix cases.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <chrono>
#include <cmath>
#include "combineall.h"
#include "Timer.h"

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

/*Small matrix case described in the paper - 
the output should be : 
{{0,1,2}, {0,1,3}, {1,2,4,5}, {1,3,5}}

@param runs Number of runs to replicate the 'known' solution case.
*/
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

/* Big matrix case to check effect of optimisation*/
void check_combine_all_big(){
	std::vector<std::vector<int> > acc;
	std::set<int> V_t;
	std::set<int> ll;
	std::set<int> X;
	std::vector<std::set<int> > solution;
	int num_rows;
	
	// 20 node run
	acc = {{0 ,1 ,1 ,1 ,0 ,1 ,-1 ,0 ,1 ,0 ,-1 ,0 ,1 ,1 ,0 ,1 ,-1 ,1 ,0 ,0} ,
		{1 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,-1 ,-1 ,0 ,1 ,0 ,0 ,-1 ,1 ,0 ,0 ,-1 ,0} ,
		{1 ,0 ,0 ,1 ,0 ,-1 ,1 ,-1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,-1 ,0 ,0 ,0 ,-1} ,
		{1 ,0 ,1 ,0 ,0 ,1 ,0 ,1 ,-1 ,1 ,-1 ,1 ,-1 ,1 ,1 ,0 ,-1 ,-1 ,0 ,-1} ,
		{0 ,1 ,0 ,0 ,0 ,-1 ,1 ,0 ,-1 ,0 ,0 ,1 ,-1 ,-1 ,1 ,-1 ,0 ,-1 ,0 ,-1} ,
		{1 ,0 ,-1 ,1 ,-1 ,0 ,-1 ,1 ,1 ,0 ,1 ,0 ,1 ,-1 ,1 ,-1 ,1 ,-1 ,0 ,-1} ,
		{-1 ,1 ,1 ,0 ,1 ,-1 ,0 ,0 ,1 ,1 ,-1 ,0 ,0 ,-1 ,-1 ,1 ,1 ,0 ,0 ,-1} ,
		{0 ,0 ,-1 ,1 ,0 ,1 ,0 ,0 ,-1 ,0 ,-1 ,-1 ,-1 ,1 ,0 ,1 ,1 ,-1 ,0 ,1} ,
		{1 ,-1 ,0 ,-1 ,-1 ,1 ,1 ,-1 ,0 ,-1 ,1 ,1 ,-1 ,1 ,0 ,0 ,1 ,1 ,0 ,-1} ,
		{0 ,-1 ,0 ,1 ,0 ,0 ,1 ,0 ,-1 ,0 ,1 ,-1 ,0 ,1 ,-1 ,1 ,0 ,0 ,0 ,-1} ,
		{-1 ,0 ,1 ,-1 ,0 ,1 ,-1 ,-1 ,1 ,1 ,0 ,-1 ,1 ,1 ,0 ,1 ,1 ,0 ,0 ,1} ,
		{0 ,1 ,0 ,1 ,1 ,0 ,0 ,-1 ,1 ,-1 ,-1 ,0 ,1 ,-1 ,1 ,-1 ,-1 ,0 ,1 ,-1} ,
		{1 ,0 ,0 ,-1 ,-1 ,1 ,0 ,-1 ,-1 ,0 ,1 ,1 ,0 ,0 ,-1 ,1 ,-1 ,0 ,0 ,-1} ,
		{1 ,0 ,0 ,1 ,-1 ,-1 ,-1 ,1 ,1 ,1 ,1 ,-1 ,0 ,0 ,1 ,-1 ,-1 ,0 ,-1 ,-1} ,	
		{0 ,-1 ,0 ,1 ,1 ,1 ,-1 ,0 ,0 ,-1 ,0 ,1 ,-1 ,1 ,0 ,1 ,-1 ,0 ,0 ,-1} ,
		{1 ,1 ,-1 ,0 ,-1 ,-1 ,1 ,1 ,0 ,1 ,1 ,-1 ,1 ,-1 ,1 ,0 ,-1 ,1 ,1 ,1} ,
		{-1 ,0 ,0 ,-1 ,0 ,1 ,1 ,1 ,1 ,0 ,1 ,-1 ,-1 ,-1 ,-1 ,-1 ,0 ,1 ,0 ,-1} ,
		{1 ,0 ,0 ,-1 ,-1 ,-1 ,0 ,-1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,-1} ,
		{0 ,-1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,-1 ,0 ,1 ,0 ,0 ,0 ,-1} ,
		{0 ,0 ,-1 ,-1 ,-1 ,-1 ,-1 ,1 ,-1 ,-1 ,1 ,-1 ,-1 ,-1 ,-1 ,1 ,-1 ,-1 ,-1 ,0}};
	
	for (int k=0; k<20; k++) {
		V_t.insert(k);
		}
	for (int i=0; i<100; i++){
		solution = combine_all(acc, V_t, ll, X);
	}
	
}



/* Big matrix case to check effect of optimisation*/
void check_combine_very_big(){
	std::set<int> V_t;
	std::set<int> ll;
	std::set<int> X;
	std::vector<std::set<int> > solution;
	int num_rows;
	std::vector<std::vector<int> > acc;
	int num_entries; // = num_rows*num_rows;
	int ij_index = 0;
	int num_solutions;
	std::vector<int> temp_row;
	std::cout << num_entries << "unique entries" << std::endl;
	
	// https://stackoverflow.com/a/28312037/4955732
	
	std::ifstream input("flatA.txt");
	int count = 0;
	std::string line;
	if (input.is_open()){
		while (!input.eof()){
			std::getline(input, line);
			count++;
		}
		input.close();
	}
	
	num_entries = count-1;
	num_rows = (int)std::sqrt(num_entries);
	std::cout << "Number of entries are: " << num_entries << ". Num rows are:" << num_rows <<" \n";
	// 
	int data[num_entries];
	
	std::ifstream input2("flatA.txt");
	for (int i = 0; i < num_entries; i++) {
        input2 >> data[i];
        }

	// and now assign each row as it comes
	std::cout<<"Miaow miaow" <<"\n";
	for (int i=0; i<num_rows; i++){
		for (int j=0; j<num_rows; j++){
			
			if (i<1){
				//acc.push_back(data[j]);
				temp_row.push_back(data[j]);
				//std::cout << data[j]<< "\n";
			}
			else{
				//acc[i].push_back(data[((i*num_rows)+j)]);
				temp_row.push_back(data[((i*num_rows)+j)]);
				//std::cout << data[(i*num_rows)+j]<< "\n";
			}
		}
		acc.push_back(temp_row);
		temp_row.clear();	
	}

	
	for (int k=0; k<num_rows; k++) {
		V_t.insert(k);
	}

	Timer timer3;
	solution = combine_all(acc, V_t, ll, X);
	std::cout << "Very large matrix tests took:" << timer3.elapsed() << "\n";
	
	// Begin writing the data
	num_solutions = solution.size();
	std::cout << "Number of solutions is: " << num_solutions << "\n";
	
	std::ofstream fw("cpp_solutions.csv", std::ofstream::out);
	if (fw.is_open()){
		for (auto soln : solution){
			for (auto every : soln){
				fw << every << ",";
			}
			fw << "\n";
		}
	fw.close();
	}
	else{
		std::cout << "Problem with opening file";
	}

}


int main(){
	// Run the 'small' 6 node case
	std::cout << "Repeat 6 node case 100 times..." << std::endl;

	int nruns = 100;
	Timer timer1;
	check_combine_all_full(nruns); // Repeat the case described in the paper 100 times.
	std::cout << "Done with 100 reps of 6 node case" << timer1.elapsed()<< "s for 100 runs" << std::endl;

	// Run the 'big' 20 node case
	std::cout << "Running 20 node case once" << std::endl;
	Timer timer2;
	check_combine_all_big();

	std::cout << "Done running 20 node case ..." << timer2.elapsed() <<" s" << std::endl;

	
	std::cout << "Very large matrix test" << "\n";
	
	check_combine_very_big();
	

}
