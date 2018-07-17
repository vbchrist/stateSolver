// ConsoleApplication2.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "minConnected.h"
#include <vector>
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

template< class T >
class mat {
public:
	mat<T>::mat(int N_, int M_, T cls) : N(N_), M(M_) {
		for (auto i = 0; i < N; ++i) {
			A.emplace_back(std::vector<T>(M, cls));
		}
	}

	inline std::vector<T>& operator[](std::size_t idx) {
		return A[idx]; 
	}
	//inline std::vector<T> operator[](std::size_t idx) {return A[idx];}

	inline mat mat::operator+(const mat& B) {
		assert(N == B.N, M == B.M);
		mat<T> C(N, M, 0);
		for (auto r = 0; r < N; ++r) {
			for (auto c = 0; c < M; ++c) {
				C[r][c] = A[r][c] + B.A[r][c];
			}
		}
		return C;
	}


	inline mat mat::operator-(const mat& B) {
		assert(N == B.N, M == B.M);
		mat<T> C(N, M, 0);
		for (auto r = 0; r < N; ++r) {
			for (auto c = 0; c < M; ++c) {
				C[r][c] = A[r][c] - B.A[r][c];
			}
		}
		return C;
	}

	inline bool mat::swap_row(const size_t& r1, const size_t& r2) {
		if (r1 >= N || r2 >= N) { return false; };
		std::swap(A[r1], A[r2]);
		return true;
	}

	int N, M;
	std::vector<std::vector<T>> A;
};

int main()
{
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


	mat<int> A(3, 4, 2);
	mat<int> B(3, 4, -1);
	
	auto C = A + B;
	auto D = A - B;
	D[0][0] = -20;
	D.swap_row(0, 2);
	
	return 0;
}