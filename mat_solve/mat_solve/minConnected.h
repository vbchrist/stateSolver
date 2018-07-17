#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include "assert.h"

typedef std::vector<int> row;
typedef std::pair<int, row> idx_row;
typedef std::vector<std::pair<int, row>> matrix;
typedef std::vector<int> eq_idx;

inline row and(const row& A, const row& B) {
	assert(A.size() == B.size());
	row C;
	C.resize(A.size());
	for (auto i = 0; i < C.size(); ++i) {
		C[i] = A[i] && B[i];
	}
	return C;
}

inline row or(const row& A, const row& B) {
	assert(A.size() == B.size());
	row C;
	C.resize(A.size());
	for (auto i = 0; i < C.size(); ++i) {
		C[i] = A[i] || B[i];
	}
	return C;
}

inline bool any(const row& A, const row& B) {
	assert(A.size() == B.size());
	for (auto i = 0; i < A.size(); ++i) {
		if (A[i] == 1 && B[i] == 1) { 
			return true; 
		}
	}
	return false;
}

inline int get_index(const matrix& M, const int i) {
	for (auto idx = 0; idx != M.size(); idx++) {
		if (M[idx].first == i) { 
			return idx;
		};
	}
	return -1;
};

inline row count(const matrix& M) {
	row count(M[0].second.size(), 0);
	for (auto r : M) {
		for (auto i = 0; i < r.second.size(); ++i) {
			if (r.second[i]) {
				count[i]++;
			}
		}
	}
	return count;
};

inline matrix connected(const matrix& M, const int& i) {
	matrix N = M;
	int idx = get_index(M, i);
	row mask = N[idx].second;
	matrix connected_set;
	connected_set.emplace_back(N[idx]);

	N.erase(N.begin() + idx);
	for (auto r : N) {
		if (any(mask, r.second)) {
			mask = or(mask, r.second);
			connected_set.emplace_back(r);
		}
	}

	row rr = count(connected_set);

	return connected_set;
}

inline matrix min_connected(const matrix& M, const int& idx) {
	
	matrix min_set = connected(M, idx);

	for (auto i = 0; i < min_set.size() - 1; ++i) {		
		//  copy the minimal set
		matrix connected_set = min_set;
		//  Remove test row from matrix
		connected_set.erase(connected_set.begin() + i);
		//  Get connected set		
		matrix temp = connected(connected_set, connected_set[0].first);
		//  If conncted set.size() < current then its not a connected row
		if (temp.size() < connected_set.size()) {
			if (i == 0) {
				return matrix();
			}
			min_set.erase(min_set.begin() + i);
			// Now that a row is removed we need to chack for connectivity again
			min_set = connected(min_set, idx);
			i--;
		}
	};
	return min_set;
}


inline void output_row(const idx_row& r) {
	std::cout << r.first << "	";
	for (auto& i : r.second) {
		std::cout << "	" << i;
	}
	std::cout << "\n";
}

inline void output(const matrix& M) {
	std::cout << "\nMatrix:\n";
	for (auto& r : M) {
		output_row(r);
	}
}

