// Reads a csv file and begins performing the CombineAll routine. 
#include <iostream> 
#include <fstream>
#include <vector>
#include <cmath>
#include "combineall.h"

std::vector<std::vector<int> > create_acc_graph(std::string filepath){
	int num_entries;
	int num_rows;
	int count = 0;
	std::vector<int> temp_row;
	std::vector<std::vector<int> > acc;

	std::ifstream input(filepath);
	// get number of entries
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
	
	std::ifstream input2(filepath);
	for (int i = 0; i < num_entries; i++) {
        input2 >> data[i];
        }

	// create 
	
	for (int i=0; i<num_rows; i++){
		for (int j=0; j<num_rows; j++){
			
			if (i<1){
				//acc.push_back(data[j]);
				temp_row.push_back(data[j]);
				//std::cout << data[j]<< std::endl;
			}
			else{
				//acc[i].push_back(data[((i*num_rows)+j)]);
				temp_row.push_back(data[((i*num_rows)+j)]);
				//std::cout << data[(i*num_rows)+j]<< std::endl;
			}
		}
		acc.push_back(temp_row);
		temp_row.clear();	
	}
	
	return acc;
}

void write_combineall_solutions(std::vector<std::set<int>> solutions){
	// Begin writing the data
	int num_solutions = solutions.size();
	std::cout << "Number of solutions is: " << num_solutions << std::endl;
	
	std::ofstream fw("combineall_solutions.csv", std::ofstream::out);
	if (fw.is_open()){
		for (auto soln : solutions){
			for (auto every : soln){
				fw << every << ",";
			}
			fw << std::endl;
		}
	fw.close();
	}
	else{
		std::cout << "Problem with opening file";
	}

	
	
	
}


int main(int argc, char* argv[]){
	std::set<int> V_t;
	std::set<int> ll;
	std::set<int> X;
	std::vector<std::set<int> > solutions;
	int num_nodes;
	
	std::cout<<"Reading txt file" <<std::endl;
	std::vector<std::vector<int> > acc = create_acc_graph(argv[1]);
	std::cout<<"...Done reading txt file" <<std::endl;
	
	num_nodes = acc.size();
	//initialise vector set
	for (int k=0; k<num_nodes; k++) {
		V_t.insert(k);
	}
	std::cout << "Starting CombineAll run..." << std::endl;
	solutions = combine_all(acc, V_t, ll, X);
	std::cout << "Done with CombineAll run..." << std::endl;
	
	write_combineall_solutions(solutions);

}
