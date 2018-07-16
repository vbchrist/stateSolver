#pragma once

#include <string>
#include "symbolicc++.h"
#include "shunting_yard.hpp"
#include "variant.h"

using namespace std;
class expression
{
public:
	expression(string e) : raw_text(e) {
		auto rpn = Shunting_Yard(raw_text);
		exp = evalRPN(rpn, v);
	};
	expression() {}; //Default constructor
	~expression() {}; //Default constructor
	inline bool contains(const variant& v);

	string raw_text = "";
	Symbolic exp;
	set<variant> v;
};


inline bool expression::contains(const variant & var)
{
	return v.find(var) != v.end();
}

/*
class linear : expression
{
public:
	linear() {}; //Default constructor
	~linear() {}; //Default constructor
};

class polynomial : expression
{
public:
	polynomial() {}; //Default constructor
	~polynomial() {}; //Default constructor
};

class nonlinear : expression
{
public:
	nonlinear() {}; //Default constructor
	~nonlinear() {}; //Default constructor
};
*/