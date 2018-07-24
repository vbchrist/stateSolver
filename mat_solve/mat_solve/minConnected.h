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
	N.remove_row(*idx); //  This is probably removing all matching 
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
	
	for (auto i : min_set) {		
		//  copy the minimal set
		auto connected_set = min_set;	
		//  Remove test row from matrix
		connected_set.remove_row(i);	
		//  Get connected set		
		auto temp = connected(connected_set, connected_set.begin());		
		//  If conncted set.size() < current then its not a connected row
		if (temp.size() < connected_set.size()) {
			min_set.remove_row(i);
			// Now that a row is removed we need to chack for connectivity again
			min_set = connected(min_set, idx);
		}
	}
	return min_set;
}

