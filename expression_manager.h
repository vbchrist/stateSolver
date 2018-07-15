#pragma once

#include <string>
#include <vector>

#include "variant.h"
#include "expression.h"

using namespace std;
class sys
{
public:
	sys(vector<string> e) : raw_text(e) {
		for (auto& exp : raw_text) {
			expressions.emplace_back(exp);
		}
	};
	sys() {}; //Default constructor
	~sys() {}; //Default constructor

	int add(vector<string> e);

	vector<string> raw_text;
	vector<expression> expressions;
	vector<variant> variants;
};

int sys::add(vector<string> e)
{
	for (auto& exp : e) {
		expressions.emplace_back(exp);
	}
	return 0;
};
