#pragma once

#include "stdafx.h"

#pragma warning(disable:4996)
//#include "interface.hpp"
#include "shunting_yard.hpp"
#include "input_delta.h"
#include "expression_manager.h"

//#include <assert>

int main()
{
	using namespace std;

	std::pair<std::string, double> tests[] =
	{
		std::make_pair("pow(--cos(1/--20),sin( cos( 10 * 3.14 / 180  ) ))", 0.99895864),
		std::make_pair("pow(-2,-3)", -0.125),
		std::make_pair("pow(3,-2)", 0.111111111),
		std::make_pair("pow(2,3)", 8),
		std::make_pair("cos ( ( 1.3 + 1 ) ^ ( 1 / 3 ) )", 0.24816952137),
		std::make_pair("3/2 + 4*(12+3)", 61.5),
		std::make_pair("cos(- 1.32001)", 0.24816576448),
		std::make_pair("-cos(1/-20)+sin(1/30)+cos(1/50)", 0.0343769071),
		std::make_pair("--cos(1/-20)+-sin(1/30)", 0.96542309955),
		std::make_pair("--cos(1/-20)--sin(1/30)", 1.03207742123),
		std::make_pair("--cos(1/--20)", 0.99875026039),
		std::make_pair("sin( cos( 90 * 3.14 / 180  ) )", 0.00079632662),
		std::make_pair("5 + (-1 + 2 )-v=8", -2),
		std::make_pair("-3^2-v", -9),
		std::make_pair("v-2+v+v", 0.666666),
		std::make_pair("2+2-v", 4),
		std::make_pair("((2*(6-1))/2)*4-v", 20.0),
		std::make_pair("-8 + 5-v", -3.0),
		std::make_pair("5 + (-1 + 2 )-v", 6.0),
		std::make_pair("2*-2-v", -4.0),
		std::make_pair("2--2-v", 4.0),
		std::make_pair("1-2^2-v", -3),
		std::make_pair("-2^2-v", -4),
		std::make_pair("-2^-2-v", -0.25),
		std::make_pair("34.5*(23+1.5)/2", 422.625),
		std::make_pair("5 + ((1 + 2) * -4) - 3", -10),
		std::make_pair("5 + ((1 + 2) * 4) - 3 ", 14),
		std::make_pair("1-(-2^2)-1", 4),
		std::make_pair("1 - (--2^2) -- 1", -2),
		std::make_pair("(4*-10-1)", -41),
		std::make_pair("-(2+3)*(4*-10-1)", 205),
		std::make_pair("-3/2 + 4*-( 12+3)", -61.5),
		std::make_pair("-3/2 + 4*(-12-3)", -61.5),
		std::make_pair("-3/2 + -4*(-12-3)", 58.5),
		std::make_pair("5 + (-1 + 2 )", 6),
		std::make_pair("-(2+3)*(4*-10-1)+100", 305),
		std::make_pair("(2+3)*-(4*10-1)+100", -95),
		std::make_pair("(-2)^2", 4),
		std::make_pair("-2^3", -8),
		std::make_pair("( 1.3 + -1 ) ^ ( 1 / 3 )", 0.66943295008),
		std::make_pair("((2*(6-1))/2)*4", 20),
		std::make_pair("( 1 + 2 ) * ( 3 / 4 ) ^ ( 5 + 6 )", 0.12670540809),
		std::make_pair("-(11 ^ (-7))", -5.13158118e-8),
		std::make_pair("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3", 3.00012207031),
		std::make_pair("-2^(-(2^(-2)))", -0.84089641525),
		std::make_pair("-2^-2^-2", -0.84089641525),
		std::make_pair("2.5^3", 15.625),
		std::make_pair("exp( 1.11 )", 3.03435839444),
		std::make_pair("ln(2)+3^5", 243.693147181),
		std::make_pair("-1*- sin( pi / -2)", -1.0),		
		std::make_pair("1--cos(pi)", 0.0),
		std::make_pair("pi*pow(9,2)", 254.4690049407732523155),
		std::make_pair("pow(2, 3)", 8),
		/*
		std::make_pair("MAX(2, 30)", 30),
		std::make_pair("MAX(200000, 3)", 200000),
		*/
	};

	string input_test1 = "pow(--cos(1/--20),sin( cos( 10 * 3.14 / 180  ) ));pow(-2,-3);pow(3,-2);pow(2,3);cos ( ( 1.3 + 1 ) ^ ( 1 / 3 ) );3/2 + 4*(12+3);cos(- 1.32001);sin( cos( 90 * 3.14 / 180  ) );5 + (-1 + 2 )-v=8;";
	string input_test2 = "ow(--cos(1/--20),sin( cos( 10 * 3.14 / 180  ) ));pow(-2,-3);pow(3,-2);pow(2,3);cos ( ( 1.3 + 1 ) ^ ( 1 / 3 ) );3/2 + 4*(12+3);cos(- 1.32001);sin( cos( 90 * 3.14 / 180  ) );5 + (-1 + 2 )-v=8;";
	string input_test3 = "ow(--cos(1/--20),sin( cos( 10 * 3.14 / 180  ) ));pow(-2,-3);pow(3,-2);pow(2,3);cos ( ( 1.3 + 1 ) ^ ( 1 / 3 ) );sin( cos( 90 * 3.14 / 180  ) );5 + (-1 + 2 )-v=8;";

	input_delta dt;
	char* o = new char[0];

	o = dt.get_changes(input_test1.c_str());
	cout << o << "\n";
	o = dt.get_changes(input_test2.c_str());
	cout << o << "\n";
	o = dt.get_changes(input_test3.c_str());
	cout << o << "\n";

	vector<string> s1, s2;
	for (auto& t : tests) {
		s1.emplace_back(t.first);
	}

	sys test;
	test.add(s1);
	test.make_matrix();

	return 0;
}

