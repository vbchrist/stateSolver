#include "stdafx.h"

//#include "minConnected.h"


#include "matrix.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <functional>
#include <string> 

/*
For n×m matrix A
j = 1
For each row i from 1 to n do

		While column j has all zero elements, j++. 
		If j>m return.

		If element aij is zero, then interchange row i with a row x>i that has axj≠0.

		Divide each element of row i by aij, thus making the pivot aij equal to one.

		For each row k from 1 to n, with k≠i, subtract row i multiplied by akj from row k.

		Return transformed matrix A.
*/

int main()
{
	using namespace std; 
	typedef row<row<double>> matrix;
	
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
	
	matrix input = {
		{ 1,0,1,1,0,0,0,0,0 }, // 0
		{ 0,0,1,1,0,0,0,0,0 }, // 1
		{ 1,0,1,0,0,0,0,0,0 }, // 2
		{ 0,1,0,0,1,0,0,0,0 }, // 3
		{ 0,1,0,0,1,0,0,0,0 }, // 4
		{ 0,0,0,0,1,0,1,1,0 }, // 5
		{ 0,0,0,0,1,0,1,1,0 }, // 6
		{ 0,1,0,0,0,0,0,0,1 }, // 7
	};

	matrix i = {
		{ 0,1,1,1,0 }, // 0
		{ 0,1,1,1,0 }, // 1
		{ 0,1,1,1,0 }, // 2
		{ 1,1,0,0,1 }, // 3
		{ 1,0,1,0,1 }, // 4
	};

	matrix M = {
		{ 0,0,3,5,0,0,6,0 },
		{ 2,6,2,5,8,0,4,0 },
		{ 0,6,0,5,2,0,6,4 },
		{ 0,6,0,5,2,0,0,4 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,4,0,0,2,9,7,4 },
		{ 0,3,0,5,0,0,6,4 },
	};

	row<bool> J = {
		{ 0,1,1,1,0 }
	};
	row<bool> K = {
		{ 1,1,0,0,1 }
	};

	cout.precision(2);
	cout << J;
	cout << K;
	auto awn = AND(J,K);
	cout << "\n";
	cout << awn;
	
	return 0;
}

