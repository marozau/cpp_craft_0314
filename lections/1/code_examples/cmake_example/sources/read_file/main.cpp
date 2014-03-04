#include <iostream>
#include <fstream>
#include <string>

int main( int argc, char* argv[] )
{
	std::ifstream input_file( SOURCE_DIR "/CMakeLists.txt" );
	std::string line;
	while( !input_file.eof() )
	{
		std::getline( input_file, line );
		std::cout << line.c_str() << std::endl;
	}
	input_file.close();
}
