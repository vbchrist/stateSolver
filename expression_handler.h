#pragma once
#include <vector>
#include <string>
#include <algorithm>

#include <symbolicc++.h>

using namespace std;
class expression_handler
{
public:
	expression_handler();
	~expression_handler();
	int add_expressions(vector<string> string_expressions);

	int remove_expressions(vector<string> string_expressions);

	//make these hold unique pointers to objects so vector doesn't loose the locations
	vector<Symbolic> master_expression_list;
	vector<Symbolic> master_variant_list;
};



expression_handler::expression_handler()
{
}


expression_handler::~expression_handler()
{
}

inline int expression_handler::add_expressions(vector<string> string_expressions)
{
	for (auto& exp : string_expressions) {

	}
	return 0;
}

inline int expression_handler::remove_expressions(vector<string> string_expressions)
{
	for (auto& exp : string_expressions) {
		//remove expressions
	}
	return 0;
}
