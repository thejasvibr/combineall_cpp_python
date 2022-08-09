#include <algorithm>
#include <set>
#include <iostream>

std::set<int> diff_set(std::set<int> A, std::set<int> B){
	std::set<int> difference;
	std::set_difference(A.begin(), A.end(), B.begin(), B.end(), 
		std::inserter(difference, difference.end()));
	return difference;
}

std::set<int> union_set(std::set<int> A, std::set<int> B){
	std::set<int> unionset;
	std::set_union(A.begin(), A.end(), B.begin(), B.end(), 
		std::inserter(unionset, unionset.end()));
	return unionset;
}

/*int main(){
	std::set<int> A,B;
	std::set<int> result;
	std::set<int> union_result;
	A = {90,100};
	B = {1,2};
	result = diff_set(A,B);
	union_result = union_set(A,B);
	for (auto jj : result){
		std::cout << jj << std::endl;
	}
	std::cout << "Miaow!!" << std::endl;
	for (auto ii : union_result){
		std::cout << ii << std::endl;
	}
	
	int setint = *A.begin();
	for (auto ii : A){
		std::cout << ii << std::endl;
	}
	std::cout << "A post union" << std::endl;
	A = union_set(A,B);
	for (auto ii : A){
		std::cout << ii << std::endl;
	}
	
	A = diff_set(A,B);
	std::cout << "Not getting B from setdiff(unionAB, B)" << std::endl
	for (auto ii : A){
		std::cout << ii << std::endl;
	}
}*/