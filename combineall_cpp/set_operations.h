/*Wrapper that implements set operations.
*/
#include <algorithm>
#include <set>
#include <iostream>

template<typename T>
struct UnorderedVectorSet {
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    std::vector<T> _data;

    UnorderedVectorSet() = default;
    UnorderedVectorSet(const std::initializer_list<T>& init) : _data(init) {}
    UnorderedVectorSet(UnorderedVectorSet&&) = default;
    UnorderedVectorSet(const UnorderedVectorSet&) = default;
    UnorderedVectorSet(std::vector<T>&& vic) : _data(std::move(vic)) {}

    UnorderedVectorSet& operator=(const UnorderedVectorSet&) = default;

    template<typename K>
        requires std::convertible_to<K, T>
    void insert(const K& value) {
        if (!this->contains(value))
            _data.emplace_back(value);
    }

    template<typename K>
        requires std::convertible_to<K, T>
    bool contains(const K& value) const {
        return std::find(_data.begin(), _data.end(), value) != _data.end();
    }

    template<typename K>
        requires std::convertible_to<K, T>
    auto find(const K& value) const {
        return std::find(_data.begin(), _data.end(), value);
    }

    void clear() {
        _data.clear();
    }

    template<typename Iterator>
    void insert(Iterator start, Iterator end) {
        for (auto it = start; it != end; ++it)
            insert(*it);
    }
    
    template<typename Iterator>
    inline auto erase(Iterator it) {
        return _data.erase(it);
    }
    
    template<class... Args>
    constexpr typename std::vector<T>::reference emplace(Args&&... args) {
        return _data.emplace_back(std::forward<Args>(args)...);
    }

    auto begin() { return _data.begin(); }
    auto end() { return _data.end(); }
    auto begin() const { return _data.begin(); }
    auto end() const { return _data.end(); }
    size_t size() const { return _data.size(); }
    bool empty() const { return _data.empty(); }
};

std::set<int> diff_set(const std::set<int>& A, const std::set<int>& B){
	std::set<int> difference;
	std::set_difference(A.begin(), A.end(), B.begin(), B.end(), 
		std::inserter(difference, difference.end()));
	return difference;
}

std::set<int> union_set(const std::set<int>& A, const std::set<int>& B){
	std::set<int> unionset;
	std::set_union(A.begin(), A.end(), B.begin(), B.end(), 
		std::inserter(unionset, unionset.end()));
	return unionset;
}
