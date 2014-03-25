// 2_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

double const POINT = 0.0001;

//double RoundByPoint(double num, int point)
//{
//	int multiplicator = 10 * point;
//	return floor(num * multiplicator + 0.5) / multiplicator;
//}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout << "There are should be one commandline argument(text file)\nExample: 1_1.exe input.txt"<< std::endl;
		return 1;
	}

	std::ifstream inputStream(argv[1]);
	std::ofstream outputStream("output.txt");
	int code_count = 0;
	std::vector<double> codes;

	inputStream >> code_count;
	for(int i = 0; i < code_count; ++i)
	{
		double code = 0.0;
		inputStream >> code;
		codes.push_back(code);
	}

	double password;

	while(inputStream >> password)
	{
		for(auto i = codes.begin(); i != codes.end(); ++i)
		{
			if (abs(*i - password) <= 0.0001)
			{
				outputStream << "YES\n";
				break;
			}
			else if(i == codes.end() - 1)
				outputStream << "NO\n";
		}
		
		//if(std::find(codes.begin(), codes.end(), RoundByPoint(password, POINT)) != codes.end())
		//	outputStream << "YES\n";
		//else
		//	outputStream << "NO\n";
	}

	inputStream.close();
	outputStream.close();
	return 0;
}

