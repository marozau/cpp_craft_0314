#include <iostream>
#include <fstream>
#include <string>

int main( int argc, char* argv[] )
{
	std::ofstream output_file( BINARY_DIR "/output_example.txt" );
	output_file << "out put file" << std::endl;
	output_file.close();
	
	std::fstream another_output_file( BINARY_DIR "/output_example.txt", std::fstream::out | std::fstream::app );
	another_output_file << "appended line" << std::endl;
	another_output_file.close();
}
