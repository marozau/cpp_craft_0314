#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main( int argc, char* argv[] )
{
	std::ifstream input_file( SOURCE_DIR "/input2.txt" );

	int n(0);
	input_file >> n;

	std::vector<double> codes;
	if(input_file)
	{
		for(auto i = 0; i < n; i++)
		{
			double code(0.0);
			input_file >> code;
			codes.push_back(double(int(code * 10000))/10000);
		}

		std::vector<double> passwords;

		while( !input_file.eof() )
		{
			double pass(0.0);
			input_file >> pass;
			passwords.push_back(double(int(pass * 10000))/10000);
		}
		input_file.close();

		std::ofstream output_file( BINARY_DIR "/output2.txt" );

		for(auto it = passwords.begin(); it != passwords.end(); it++)
		{
			if(std::find(codes.begin(), codes.end(), *it) == codes.end())
				output_file << "NO" << std::endl;
			else
				output_file << "YES" << std::endl;
		}

		output_file.close();
	}
}
