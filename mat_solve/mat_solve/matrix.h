#pragma once

#include <vector>
#include <assert.h>

#include <algorithm>
//#include <iostream>
//#include <functional>
//#include <string> 



template< class T >
class row {
public:
	row() {};

	row(const std::initializer_list<T> l) : A(l) {};

	row(const std::vector<T>& vec) : A(vec) {};

	row(const row<T>& vec) : A(vec.A) {};

	inline T& operator[](std::size_t idx) {
		return A[idx];
	}

	inline row operator+(const row& B) const {
		assert(A.size() == B.size());
		row C;
		C.reserve(A.size());
		std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(C), std::plus<T>());
		return C;
	}

	inline row operator+(const T& B) const {
		row C;
		C.reserve(A.size());
		std::transform(
			A.begin(),
			A.end(),
			std::back_inserter(C),
			[&B](const T& x) {
			return x + B;
		});
		return C;
	}

	inline row operator-(const row& B) const {
		assert(A.size() == B.size());
		row C;
		C.reserve(A.size());
		std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(C), std::minus<T>());
		return C;
	}

	inline row operator-(const T& B) const {
		row C;
		C.reserve(A.size());
		std::transform(
			A.begin(),
			A.end(),
			std::back_inserter(C),
			[&B](const T& x) {
			return x - B;
		});
		return C;
	}

	inline row operator*(const row& B) const {
		assert(A.size() == B.size());
		row C;
		C.reserve(A.size());
		std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(C), std::multiplies<T>());
		return C;
	}

	inline row operator*(const T& B) const {
		row C;
		C.reserve(A.size());
		std::transform(
			A.begin(),
			A.end(),
			std::back_inserter(C),
			[&B](const T& x) {
			return x * B;
		});
		return C;
	}

	inline row operator/(const row& B) const {
		assert(A.size() == B.size());
		row C;
		C.reserve(A.size());
		std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(C), std::divides<T>());
		return C;
	}

	inline row operator/(const T& B) const {
		row C;
		C.reserve(A.size());
		std::transform(
			A.begin(),
			A.end(),
			std::back_inserter(C),
			[&B](const T& x) {
			return x / B;
		});
		return C;
	}

	inline auto size() const {
		return A.size();
	}

	inline void reserve(size_t size) {
		A.reserve(size);
	}

	inline void push_back(T i) {
		A.push_back(i);
	}

	const auto begin() const {
		return A.begin();
	}

	const auto end() const {
		return A.end();
	}

	inline void swap(size_t r1, size_t r2) {
		assert(r1 < A.size() && r2 < A.size());
		std::swap(A[r1], A[r2]);
	}

	std::string print() {
		std::string output;
		for (auto& idx : A) {
			output << idx << " ";
		}
		return output;
	}

	typedef T value_type;

private:
	std::vector<T> A;
};



template<class T>
std::ostream& operator<<(std::ostream &o, row<row<T>> &M)
{
	for (size_t i = 0; i < M.size(); ++i) {
		for (size_t j = 0; j < M[i].size(); ++j) {
			o << "	" << M[i][j];
		}
		o << "\n";
	}
	o << "\n";
	return o;
};


typedef row<row<double>> matrix;

bool GuassJordan(matrix& M) {

	std::vector<std::pair<size_t, size_t>> pivots;
	// Increase i by 1 and j by 1 to choose the new pivot element. Return to Step 1.
	size_t pivot_row = 0;
	for (size_t j = 0; j < M[0].size(); ++j) {
		bool pivot = false;
		for (size_t k = pivot_row; k < M.size(); ++k) {
			// If aij = 0 swap the i-th row with some other row below to guarantee that aij 6= 0.
			if (!pivot && M[k][j] != 0) {
				M.swap(pivot_row, k);
				pivot = true;
				k = pivot_row;
				pivots.push_back(std::make_pair(k, j));
			}
			if (pivot) {
				// Divide the i - th row by aij to make the pivot entry = 1.
				if (k == pivot_row) {
					M[k] = M[pivot_row] / M[pivot_row][j];
				}
				// Eliminate all other entries in the j-th column by subtracting suitable multiples of the ith row from the other rows.
				else {
					M[k] = M[k] - M[pivot_row] * M[k][j];
				}
			}
		}
		if (pivot) { pivot_row++; }
	}

	for (size_t p = pivots.size(); p-- > 0;) {
		for (size_t k = pivots[p].first; k-- > 0;) { // unsigned can't evaluate at >= 0 bc it wraps
			M[k] = M[k] - M[pivots[p].first] * M[k][pivots[p].second];
		}
	}
	return true;
}