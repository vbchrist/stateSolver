#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <math.h> 
#include <set>
#include <algorithm>

#include <iomanip>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/function.hpp>
#include <boost/math/tools/minima.hpp>

#include <symbolicc++.h>

#include <exprtk.hpp>


inline std::pair<unsigned int, bool> precedence_associativity(const std::string& token) {
	typedef std::pair<unsigned int, bool> pair_;

	if (token == "(") {
		return pair_(0, 0);
	};
	if (token == "-") {
		return pair_(2, 0);
	};
	if (token == "+") {
		return pair_(2, 0);
	};
	if (token == "/") {
		return pair_(3, 0);
	};
	if (token == "*") {
		return pair_(3, 0);
	};
	if (token == "--") {
		return pair_(4, 1);
	};
	if (token == "^") {
		return pair_(4, 1);
	};
	return pair_(5, 1);
}

//  https://en.wikipedia.org/wiki/Shunting-yard_algorithm
std::vector<std::string> Shunting_Yard(std::string& expression) {
	using namespace std;
	
    vector<string> output;
	vector<string> stack;
	
	vector<string> tokens_string;

	boost::erase_all(expression, " ");
	boost::char_separator<char> sep("", "=,+-*/^!%()");
	boost::tokenizer<boost::char_separator<char>> tokens(expression, sep);

	string last_t = "";
	bool exp = false;
	for (const auto& t : tokens) {
		bool expression = false;
		if (t == "(") {
			//  If the incoming symbol is a left parenthesis, 
			//  push it on the stack.
			stack.push_back(t);
		}


		else if (exprtk::details::is_base_function(t)) {
			//  If the token is a function token, 
			//  then push it onto the stack.
			/*
			    "abs", "acos",  "acosh", "asin",  "asinh", "atan",  "atanh",
                "atan2",  "avg",  "ceil",  "clamp",  "cos",  "cosh",  "cot",
                "csc",  "equal",  "erf",  "erfc",  "exp",  "expm1", "floor",
                "frac", "hypot", "iclamp",  "like", "log", "log10",  "log2",
                "logn", "log1p", "mand", "max", "min", "mod", "mor",  "mul",
                "ncdf",  "pow",  "root",  "round",  "roundn",  "sec", "sgn",
                "sin", "sinc", "sinh", "sqrt", "sum", "swap", "tan", "tanh",
                "trunc",  "not_equal",  "inrange",  "deg2grad",   "deg2rad",
                "rad2deg", "grad2deg"
			*/
			stack.push_back(t);
		}

		else if (t == ")" || t == ",") {
			//  If the incoming symbol is a right parenthesis: 
			//  discard the right parenthesis, 
			//  pop and print the stack symbols until you see a left parenthesis. 
			//  Pop the left parenthesis and discard it.
			string stack_op = stack.back();
			while (stack_op != "(") {
				stack.pop_back();
				output.push_back(stack_op);
				stack_op = stack.back();
			}
			if (t == ")") {
				stack.pop_back();
			}
		}

		else if (t == "+" || t == "-" || t == "*" || t == "/" || t == "^" || t == "=") {
			bool op_stored = true;			

			// If incoming symbol is "=" then we should assume it is -(remaining)

			string tt = t;
			if (t == "=") {
				tt = "-";
				exp = true;
			}
			if (tt == "-") {
				if (last_t ==  "" ||
					last_t == "(" ||
					last_t == "," ||
					last_t == "+" ||
					last_t == "-" ||
					last_t == "*" ||
					last_t == "/" ||
					last_t == "^") 
				{
					tt = "--";
				}
			}

			while (op_stored) {

				//  If the incoming symbol is an operator and the stack is empty 
				//  or contains a left parenthesis on top, 
				//  push the incoming operator onto the stack.
				if (stack.size() == 0) {
					stack.push_back(tt);
					op_stored = false;
				}
				else {
					string stack_op = stack.back();
					if (stack_op == "(") {
						stack.push_back(tt);
						op_stored = false;
					}

					//  If the incoming symbol is an operator 
					//  and has either higher precedence than the operator on the top of the stack, 
					//  or has the same precedence as the operator on the top of the stack 
					//  and is right associative -- push it on the stack.
					else if (precedence_associativity(tt).first > precedence_associativity(stack_op).first ||
						(precedence_associativity(tt).first == precedence_associativity(stack_op).first && precedence_associativity(tt).second))
					{
						stack.push_back(tt);
						op_stored = false;
					}

					//  If the incoming symbol is an operator 
					//  and has either lower precedence than the operator on the top of the stack, 
					//  or has the same precedence as the operator on the top of the stack 
					//  and is left associative-- continue to pop the stack until this is not true.
					//  Then, push the incoming operator.
					else {
						stack.pop_back();
						output.push_back(stack_op);
					}
				}
			}
			if (t == "=") {
				stack.push_back("(");
			}
		}

		else {
			//if (is_function) {
			//  If the incoming symbol is a function,
			//  push it on the stack.
			//output.push_back(t);
			//}
			//else {
			//  If the incoming symbol is an operand, 
			//  send to output.
			output.push_back(t);
			//}
		}
		last_t = t;
	}

	if (exp) {
		string stack_op = stack.back();
		while (stack_op != "(") {
			stack.pop_back();
			output.push_back(stack_op);
			stack_op = stack.back();
		}
		stack.pop_back();
	}

	//  At the end of the expression, 
	//  pop and print all operators on the stack. 
	//  (No parentheses should remain.)
	while (stack.size() > 0) {
		string stack_op = stack.back();
		stack.pop_back();
		output.push_back(stack_op);
	}

	return output;
};

Symbolic evalRPN(std::vector<std::string>& tokens) {

	//https://discuss.leetcode.com/topic/62487/clean-c-standard-solution-with-stack

	std::stack<Symbolic> nums;
	//is_func is_function;

	for (auto& t : tokens) {
		if (t == "+" || t == "-" || t == "*" || t == "/" || t == "^") {

			Symbolic n2 = nums.top();
			nums.pop();
			Symbolic n1 = nums.top();
			nums.pop();

			if (t == "+") { nums.push(n1 + n2); }
			else if (t == "-") { nums.push(n1 - n2); }
			else if (t == "*") { nums.push(n1 * n2); }
			else if (t == "/") { nums.push(n1 / n2); }
			else if (t == "^") { nums.push(n1 ^ n2); }
		}
		else if (t == "--") {
			Symbolic n1 = nums.top();
			nums.pop();
			nums.push(Symbolic(double(-1)) * n1);
		}
		else if (exprtk::details::is_base_function(t)) {
			/*
				sin,cos,tan,cot,sec,csc,sinh,cosh,ln,log
			*/
			Symbolic n1 = nums.top();
			nums.pop();
			if (t == "sin") {
				nums.push(sin(n1));
			}
			if (t == "cos") {
				nums.push(cos(n1));
			}
			if (t == "tan") {
				nums.push(cos(n1));
			}
			if (t == "sec") {
				nums.push(sec(n1));
			}
			if (t == "csc") {
				nums.push(csc(n1));
			}
			if (t == "cot") {
				nums.push(cot(n1));
			}
			if (t == "sinh") {
				nums.push(sinh(n1));
			}
			if (t == "cosh") {
				nums.push(cosh(n1));
			}
			if (t == "ln") {
				nums.push(ln(n1));
			}
			if (t == "exp") {
				nums.push(exp(n1));
			}
			if (t == "sqrt") {
				nums.push(sqrt(n1));
			}
			if (t == "pow") {
				assert(nums.size() >= 1);
				Symbolic n2 = nums.top();
				nums.pop();
				nums.push(n2^n1); //RPN means args are in reverse order
			}
		}
		else {
			if (t.find_first_not_of("0123456789.") == std::string::npos) {
				nums.push(std::stod(t));
			} else {
				nums.push(Symbolic(t));
			}
		}
	}
	return nums.top();
};