#include "ccsearch.cpp"
#include <fstream>
#include <cmath>

void check_kreissig_bigmat(){
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

	
	
	cCCSearch uu;
	uu.findCCIS(acc);
	for (auto ii : uu.solution_set){
		std::cout << "soln start: " << std::endl;
		for (auto jj : ii){
			std::cout << jj << "\n";
		}
	}
	
}


void check_ky2013_example(){
	
	std::cout << "hi" << "\n";
	// initialise input data
	std::vector<std::vector<int> > acc;
	std::vector<std::vector<int> >  out;
	
	acc = {{ 0, 1, 0, 0,-1,-1}, 
		   { 1, 0, 1, 1, 0, 1},
		   {0, 1,  0,-1, 1,  0},
		   {0, 1, -1, 0,-1,  0},
		   {-1, 0, 1,-1, 0, 1},
		   {-1, 1, 0, 0, 1, 0}};
	// 
	cCCSearch uu;
	//uu.adjM = acc;
	uu.findCCIS(acc);
	for (auto ii : uu.solution_set){
		std::cout << "soln start: " << std::endl;
		for (auto jj : ii){
			std::cout << jj << "\n";
		}
	}
}

int main(){
	check_ky2013_example();
	check_kreissig_bigmat();
	return 0;
}