#pragma once

#include <string>
#include "symbolicc++.h"
#include "shunting_yard.hpp"

using namespace std;
class expression
{
public:
	expression(string e) : raw_text(e) {
		auto rpn = Shunting_Yard(raw_text);
		exp = evalRPN(rpn);
	};
	expression() {}; //Default constructor
	~expression() {}; //Default constructor
	string raw_text = "";
	Symbolic exp;
};
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