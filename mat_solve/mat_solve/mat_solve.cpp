// ConsoleApplication2.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "minConnected.h"

int main()
{
	/*
	std::vector<row> input = {
		{ 0,1,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0,1 },
		{ 1,1,0,1,0,0,0,1,0,1,0 },
		{ 0,0,0,0,1,1,1,0,0,0,1 },
		{ 1,1,0,1,0,0,0,0,0,0,1 },
		{ 0,0,0,0,1,0,0,0,1,0,0 },
		{ 0,1,0,1,0,0,0,0,0,0,0 },
		{ 1,0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,1,0,1,0,0,0,1,0 },
		{ 0,1,0,0,0,0,1,0,0,0,1 },
		{ 0,0,0,1,0,0,1,0,0,1,0 },
		{ 0,0,1,0,0,1,0,1,0,1,0 },
		{ 0,1,1,1,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,1,1,0,1,1 }
	};*/

	std::vector<row> input = {
		{ 1,0,1,1,0,0,0,0 },
		{ 0,0,1,1,0,0,0,0 },
		{ 1,0,1,0,0,0,0,0 },
		{ 0,1,0,0,1,0,0,0 },
		{ 0,1,0,0,1,0,0,0 },
		{ 0,0,0,0,1,0,1,1 },
		{ 0,0,0,0,1,0,1,1 },
	};

	matrix M;
	size_t rowlength = input[0].size();
	for (auto idx = 0; idx != input.size(); idx++) {
		assert(input[idx].size() == rowlength);
		M.push_back(std::make_pair(idx, input[idx]));
	}
	matrix s;
	for (int i = 0; i < 1000; i++) {
		s = min_connected(M, 4);
	}
	output(s);
	
	return 0;
}