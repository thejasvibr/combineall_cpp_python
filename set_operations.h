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
