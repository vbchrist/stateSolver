#pragma once

#include <assert.h>
#include "matrix.h"

template<class T, class U>
class expr : public row<T> {
	// construct from expression & ptr to var list
	U expression;
};

template<class T>
inline int count(const T& i) {
	if (i != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

template<class T>
inline int count(const row<T>& M) {
	int c = 0;
	for (auto r : M) {
		c += count(r);
	}
	return c;
}

template<class T>
inline row<row<T>> connected(const row<row<T>>& M, typename std::vector<row<T>>::iterator idx) {
	row<T> mask = *idx;
	row<row<T>> N(M);
	N.remove_row(idx); //  This is probably removing all matching 
	row<row<T>> connected_set;	
	connected_set.add_row(mask); 
	for (auto r : N) {
		auto shared = and(mask, r);
		if (count(shared) > 0) {
			mask = or(mask, r);
			connected_set.add_row(r); 
		}
	}
	return connected_set;
};

template<class T>
inline row<row<T>> min_connected(const row<row<T>>& M, typename std::vector<row<T>>::iterator idx) {	
	auto min_set = connected(M, idx);
	min_set.remove_row(idx);
	for(auto it = min_set.begin(); it != min_set.end(); min_set++) {
		auto temp = connected(min_set, idx);
		if (temp.size() < min_set.size()) {
			min_set.remove_row(it);
			min_set = temp;
		}
	}
	min_set.add_row(*idx);

	//Trim hanging variables
	return min_set;
}

