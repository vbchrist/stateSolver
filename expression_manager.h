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
	int make_matrix();

	vector<string> raw_text;
	vector<expression> expressions;
	set<variant> variants;

private:
};

int sys::add(vector<string> e)
{
	for (auto& exp : e) {
		expression ex(exp);
		expressions.emplace_back(ex);
		variants.insert(ex.v.begin(), ex.v.end());
	}
	return 0;
}
inline int sys::make_matrix()
{
	vector<vector<bool>> matrix;
	vector<bool> row;

	row.resize(variants.size());
	for (auto& e : expressions) {

		set<variant>::iterator it = variants.begin();
		for (int i = 0; i < row.size(); i++) {
			if (e.contains(*it)) {
				row[i] = true;
			}
			else {
				row[i] = false;
			}
			it++;
		}
		matrix.emplace_back(row);
	}
	return 0;
}
;
