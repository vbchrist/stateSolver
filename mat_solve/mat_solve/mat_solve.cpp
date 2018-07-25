#include "stdafx.h"

//#include "minConnected.h"



#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <functional>
#include <string> 

#include "matrix.h"
#include "minConnected.h"

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
	typedef row<node<bool, int>> matrix;
	
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
	
	matrix j = {
		node<bool, int>(1,{ 1, 0, 0, 0, 1 }),
		node<bool, int>(2,{ 0, 1, 1, 1, 0 }),
		node<bool, int>(3,{ 0, 1, 1, 0, 0 }),
		node<bool, int>(4,{ 0, 0, 1, 1, 0 }),
		node<bool, int>(5,{ 1, 1, 0, 0, 1 }),
	};



	/*
	row<bool> J = {
		{ 0,1,1,1,0 }
	};

	row<bool> K = {
		{ 1,1,0,0,1 }
	};
	*/

	cout.precision(2);
	auto match = j.match(node<bool, int>(4, { 0, 0, 1, 1, 0 }));
	//	cout << *match << "\n";
	//cout << min_connected(j, match) << "\n";
	
	return 0;
}

