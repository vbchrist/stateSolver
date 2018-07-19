// ConsoleApplication2.cpp : Defines the entry point for the console application.

#include "stdafx.h"

//#include "minConnected.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <functional>

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


template< class T >
class row {
public:

	row(){};
	row(const row<T>& vec) : A(vec.A) {};
	row(const std::vector<T>& vec) : A(vec) {};
	
	inline T& operator[](std::size_t idx) {
		return A[idx];
	}
	inline row operator+(const row& B) {
		assert(A.size() == B.size());
		row result;
		result.reserve(A.size());
		std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(result), std::plus<T>());
		return result;
	}
	inline row operator-(const row& B) {
		assert(A.size() == B.size());
		row C;
		A.reserve(A.size());
		std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(C), std::minus<T>());
		return C;
	}
	inline row operator*(const row& B) {
		assert(A.size() == B.size());
		row C;
		A.reserve(A.size());
		std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(C), std::multiplies<T>());
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

template< class T >
class matrix {
public:
	matrix() {};
	matrix(const matrix<T>& M) : A(M.A) {};
	matrix(const std::vector<row<T>>& M) : A(M) {};
	matrix(const std::vector<std::vector<T>>& M) {
		std::vector<row<T>> result;
		result.reserve(M.size());
		size_t size = M[0].size();
		for (auto&& r : M) {
			assert(r.size() == size);
			A.emplace_back(r);
		}
	};

	inline row<T>& operator[](std::size_t idx) {
		return A[idx];
	}

private:
	std::vector<row<T>> A;
};

/*
template<class T>
std::ostream& operator<<(std::ostream &o, const row<T> &B)
{
	std::string s = B.print();
	return o;
}
*/

int main()
{
	using namespace std;

	/*
	std::vector<row> input = {
		{ 1,1,0,0,1,0,0,1,0,0,0 },
		{ 0,0,0,0,1,0,1,0,0,0,1 },
		{ 1,1,0,1,0,0,0,1,0,1,0 },
		{ 0,0,1,0,1,0,1,1,0,0,1 },
		{ 1,1,0,1,0,0,0,0,0,0,1 },
		{ 0,0,0,0,1,0,1,0,1,0,0 },
		{ 0,1,0,1,0,0,0,0,0,0,0 },
		{ 1,0,0,0,0,0,1,1,0,1,0 },
		{ 0,0,0,1,0,0,0,0,0,1,0 },
		{ 0,0,0,1,1,0,1,0,0,0,1 },
		{ 0,0,0,1,0,0,1,0,0,1,0 },
		{ 0,1,0,0,0,1,0,1,0,1,0 },
		{ 0,1,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,1,1,0,1,1 }
	};
	*/

	/*
		std::vector<row> input = {
		{ 1,0,1,1,0,0,0,0,0 }, // 0
		{ 0,0,1,1,0,0,0,0,0 }, // 1
		{ 1,0,1,0,0,0,0,0,0 }, // 2
		{ 0,1,0,0,1,0,0,0,0 }, // 3
		{ 0,1,0,0,1,0,0,0,0 }, // 4
		{ 0,0,0,0,1,0,1,1,0 }, // 5
		{ 0,0,0,0,1,0,1,1,0 }, // 6
		{ 0,1,0,0,0,0,0,0,1 }, // 7
	};

	*/

	row<int> A({ 7,6,5,0 });
	row<int> B({ 2,2,3,0 });
	matrix<int> M({ { 2,2,3,0 }, { 2,2,3,0 }, { 2,2,3,0 } });


	row<int> C = A + B;
	row<int> D = A - B;
	row<int> E = A * B;

	auto aa = M[1][2];
	
	return 0;
}

