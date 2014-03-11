#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main( int argc, char* argv[] )
{
	setlocale(LC_ALL, ".1251");

	std::ifstream input_file( BINARY_DIR "/input1.txt" );
	std::vector<std::string> strings;
	std::string chars(" -\\");

	if(input_file)
	{
		while( !input_file.eof() )
		{
			std::string line;
			std::getline( input_file, line );

			for(auto i = 0; i < chars.length(); i++)
			{
				line.erase(std::remove(line.begin(), line.end(), chars.c_str()[i]), line.end());
			}

			std::transform(line.begin(), line.end(), line.begin(), ::tolower);

			if(strings.size() > 0)
				std::reverse(line.begin(), line.end());

			strings.push_back(line);
		}
		input_file.close();

		std::ofstream output_file( BINARY_DIR "/output1.txt" );

		for(auto it = strings.begin() + 1; it != strings.end(); it++)
		{
			if(strings.at(0).find(*it) == std::string::npos)
				output_file << "NO" << std::endl;
			else
				output_file << "YES" << std::endl;
		}

		output_file.close();
	}
}
