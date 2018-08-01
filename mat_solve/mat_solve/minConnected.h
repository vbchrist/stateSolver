#pragma once

#include <assert.h>
#include <memory>

#include <iostream>

#include "matrix.h"


template<class U, class T>
class node : public row<T> {
public:
	node() {};
	
	node(const U& val, const std::initializer_list<T> l) : row<T>(l), expression(val) {};

	node(const U& val, const std::vector<T>& vec) : row<T>(vec), expression(val) {};

	node(const U& val, const row<T>& vec) : row<T>(vec.A), expression(val) {};

	node(const node<U, T>& n) : row<T>(n.A), expression(n.expression) {};

	inline bool operator==(const node<U, T>& B) const {
		return expression == B.expression;
	}

	inline bool operator<(const node<U, T>& B) const {
		return expression < B.expression;
	}

	U expression;
};

//  Dragons!
//  https://stackoverflow.com/questions/14384880/how-to-prevent-specialization-of-stdvectorbool
typedef node<int, int> expr;
typedef row<expr> matrix;

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

inline matrix no_hanging(matrix M) {

	for (auto v = 0; v < M[0].size(); v++) {
		int v_count = 0;
		std::vector<expr>::const_iterator remove_row = M.end();

		for (auto r_it = M.begin(); r_it != M.end(); ++r_it) {
			auto current_row = *r_it;
			if (current_row[v] == 1) {
				v_count++;
				remove_row = r_it;
			}
		}
		if (v_count == 1) {
			M.remove_row(remove_row);
		}
	}
	return M;
}

template<class T, class U>
inline matrix connected(matrix M, node<U, T> mask) {
	matrix connected_set;
	row<T>* mask_ptr = &mask;  //make ptr to mask to cast for template func overload
	connected_set.add_row(mask);
	M.remove_row(M.match(mask));

	std::vector<expr>::const_iterator r = M.begin();
	while(r != M.end()) {
		row<T> shared = and(*mask_ptr, *r);
		row<T>* shared_ptr = &shared;  //make ptr to shared to cast for template func overload
		auto share_count = count(shared);
		if(share_count > 0){
			*mask_ptr = or(*mask_ptr, *r); 
			connected_set.add_row(*r);
			M.remove_row(r);
			r = M.begin();
		}
		else {
			r++;
		}
	}
	connected_set.sort();
	return connected_set;
};

template<class T, class U>
inline matrix min_connected(matrix M, node<U, T> mask) {

	// STEP 0
	// Remove hanging variables

	matrix min_set = connected(M, mask);
	 

	// STEP 1
	// Remove hanging variables
	// If row removed GOTO STEP 1
	min_set = no_hanging(min_set);
	std::cout << "?";

	// STEP 2 (is this required?)
	// For each row in set
	//		Remove row
	//		Get connected set
	//		If set < min_set && rank > 1? && set > 1 then
	//			Return new global min set
	// If row removed GOTO STEP 1
	

	// STEP 3
	// For earch var:
	//		Replace rows with or(reduced_row, current_row)
	//		Repeat until target is univar or unsolvable
	// If not all rows used make new min set
	// GOTO STEP 1


	// Return set

	return min_set;
}

template<class U, class T>
std::ostream& operator<<(std::ostream &o, node<U, T> &M)
{
	return o << M.print();
};

