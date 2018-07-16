#pragma once

#include <string>
#include <string>

class variant
{
public:
	variant(std::string token_) : token(token_) {};
	variant() {}; //Default constructor
	~variant() {}; //Default constructor
	//inline bool operator==(const X& lhs, const X& rhs) { /* do actual comparison */ }
	//inline bool operator!=(const X& lhs, const X& rhs) { return !operator==(lhs, rhs); }
	inline bool operator< (const variant& rhs) const { return (token < rhs.token); }
	//inline bool operator> (const X& lhs, const X& rhs) { return  operator< (rhs, lhs); }
	//inline bool operator<=(const X& lhs, const X& rhs) { return !operator> (lhs, rhs); }
	//inline bool operator>=(const X& lhs, const X& rhs) { return !operator< (lhs, rhs); }
	std::string token = "";
	double value = 0.0;
};
