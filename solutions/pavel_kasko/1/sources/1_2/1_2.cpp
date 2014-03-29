#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

double const POINT = 0.0001;

int main(int argc, char* argv[])
{
	std::ifstream inputStream(BINARY_DIR "/input.txt");
	std::ofstream outputStream(BINARY_DIR "/output.txt");
    
    if(!inputStream.good())
    {
        std::cout << "Couldn't open files!\n";
        return 1;
    }
    
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
	}

	inputStream.close();
	outputStream.close();
	return 0;
}
