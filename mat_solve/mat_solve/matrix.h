#pragma once
#include <vector>
#include <assert.h>
#include <algorithm>

/*

Following is the list of operators which can be overloaded −

+	-	*	/	%	^
&	|	~	!	,	=
<	>	<=	>=	++	--
<<	>>	==	!=	&&	||
+=	-=	/=	%=	^=	&=
|=	*=	<<=	>>=	[]	()
->	->*	new	new []	delete	delete []

*/

template<class T>
class row {
public:
	row() {};
	
	row(const size_t size) {
		A.resize(size);
	};

	row(const std::initializer_list<T> l) : A(l) {};

	row(const std::vector<T>& vec) : A(vec) {};

	row(const row<T>& vec) : A(vec.A) {};

	inline T& operator[](std::size_t idx) {
		return A[idx];
	}

	inline bool operator==(const row<T>& B) const {
		return A == B.A;
	}

	inline row operator+(const row& B) const {
		assert(A.size() == B.size());
		row C;
		C.reserve(A.size()); //  faster than resize() which calls constructor
		std::transform(
			A.begin(), 
			A.end(), 
			B.begin(), 
			std::back_inserter(C), 
			std::plus<T>());
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

	inline void add_row(const T& r) {
		return A.emplace_back(r);
	}

	inline void remove_row(const typename std::vector<T>::iterator& r) {
		A.erase(r);
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

	inline auto match(const T &idx)
	{
		if (!std::is_sorted(A.begin(), A.end())) {
			std::sort(A.begin(), A.end());
		}
		return binary_search(A.begin(), A.end(), idx);  // Returns only T/F
	};

	std::string print() {
		std::string output;
		for (auto& idx : A) {
			output << idx << " ";
		}
		return output;
	}

	typedef T value_type;
	
	std::vector<T> A;
};

template<class T>
bool and(const T &A, const T &B)
{
	return A && B;
};

template<class T>
row<T> and(const row<T> &A, const row<T> &B)
{
	assert(A.size() == B.size());
	row<T> C;
	C.reserve(A.size());
	std::transform(
		A.begin(), 
		A.end(), 
		B.begin(), 
		std::back_inserter(C), 
		[](const T& a_, const T& b_) {
			return and(a_,b_);
	});
	return C;
};

template<class T>
bool or(const T &A, const T &B)
{
	return A || B;
};

template<class T>
row<T> or(const row<T> &A, const row<T> &B)
{
	assert(A.size() == B.size());
	row<T> C;
	C.reserve(A.size());
	std::transform(
		A.begin(),
		A.end(),
		B.begin(),
		std::back_inserter(C),
		[](const T& a_, const T& b_) {
			return or (a_, b_);
		});
	return C;
};

template<class T>
bool not(const T &A)
{
	return !A;
};

template<class T>
row<T> not(const row<T> &A)
{
	row<T> C;
	C.reserve(A.size());
	std::transform(
		A.begin(),
		A.end(),
		std::back_inserter(C),
		[](const T& x) {
			return not(x);
		});
	return C;
};

template<class T>
std::ostream& operator<<(std::ostream &o, row<row<T>> &M)
{
	for (auto&& r : M) {
		for (auto&& c : r) {
			o << "	" << c;
		}
		o << "\n";
	}	
	return o;
};

template<class T>
std::ostream& operator<<(std::ostream &o, row<T> &M)
{
	for (auto&& r : M) {
		o << "	" << r;
	}
	return o;
};

template<class T>
bool GuassJordan(row<row<T>>& M) {

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