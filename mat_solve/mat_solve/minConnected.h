#pragma once

#include <assert.h>
#include "matrix.h"




template<class U, class T>
class node : public row<T> {
public:
	node() {};

	node(const U& val, const std::initializer_list<T> l) : row<T>(l), expression(val) {};

	node(const U& val, const std::vector<T>& vec) : row<T>(vec), expression(val) {};

	node(const U& val, const row<T>& vec) : row<T>(vec.A), expression(val) {};

	inline bool operator==(const node<U,T>& B) const {
		return expression == B.expression;
	}

	inline bool operator<(const node<U,T>& B) const {
		return expression < B.expression;
	}

	U expression;
};

typedef row<node<bool, int>> matrix;
typedef node<bool, int> expr;

template<class T, class U>
std::ostream& operator<<(std::ostream &o, node<U,T> &M)
{
	for (auto&& r : M) {
		o << M.expression << "	" << M.print();
	}
	return o;
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

template<class T, class U>
inline matrix connected(const matrix& M, const node<U,T>& mask) {
	matrix connected_set;
	connected_set.add_row(mask); 
	for (auto r : M) {
		auto shared = and(mask, r);
		if (count(shared) > 0) {
			mask = or(mask, r);
			connected_set.add_row(r); 
		}
	}
	return connected_set;
};

template<class T, class U>
inline matrix min_connected(const matrix& M, typename std::vector<node<U,T>>::iterator idx) {
	auto min_set = connected(M, idx);
	for(auto it = min_set.begin(); it != min_set.end(); it++) {
		auto temp = connected(min_set, idx);
		if (temp.size() < min_set.size()) {
			//min_set.remove_row(it);
			min_set = temp;
		}
	}
	min_set.add_row(*idx);

	//Trim hanging variables
	return min_set;
}

