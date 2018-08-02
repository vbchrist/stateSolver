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

TODO:
	1. Minimial connected set (10 hours)
	2. Solve order (do all numerically for WCS testing) (16 hourS)
	3. Return input text with ID tags for variables (10 hours)
	3. Compile solver from expressions (20 hours)

Current time-to-complete 30-60 hours
*/

int main()
{
	using namespace std;

	matrix j = {
		expr(1,{ 1, 1, 1, 1, 1 }),
		expr(2,{ 0, 1, 1, 1, 0 }),
		expr(3,{ 1, 1, 1, 0, 1 }),
		expr(4,{ 0, 0, 1, 1, 0 }),
		expr(5,{ 1, 0, 0, 0, 0 }),
	};

	cout.precision(2);
	auto s = node<int, int>(4, { 0, 0, 1, 1, 0 });
	cout << *j.match(s) << "\n";

	auto test = min_connected(j, s);

	return 0;
}