#include "stdafx.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <functional>
#include <string> 

#include "matrix.h"
#include "minConnected.h"

/*

Data structure:

Matrix of Expressions X raw_variants
Matrix of Steams X stream_variants
Matrix of Mixtures X mix_variants
Matrix of Fluids X properties_variants

Generic:
Matrix of Containers X variants

expr(container,{vars})
expr(1,{ 1, 0, 0, 0, 1 })

*/

int main()
{
	using namespace std; 
	
	matrix j = {
		expr(1,{ 1, 0, 0, 0, 1 }),
		expr(2,{ 0, 1, 1, 1, 0 }),
		expr(3,{ 0, 1, 1, 0, 0 }),
		expr(4,{ 0, 0, 1, 1, 0 }),
		expr(5,{ 1, 1, 0, 0, 1 }),
	};

	cout.precision(2);
	auto s = node<int, bool>(4, { 0, 0, 1, 1, 0 });
	cout << *j.match(s) << "\n";

	auto test = min_connected(j, s);

	return 0;
}

