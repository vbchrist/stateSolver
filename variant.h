#pragma once

#include <string>


class variant
{
public:
	variant(std::string token_) : token(token_) {};
	variant() {}; //Default constructor
	~variant() {}; //Default constructor
	std::string token = "";
	double value = 0.0;
};
