#include <iostream>
#include <fstream>
#include <string>
using namespace std;
namespace Paths
{
    const string input_file = SOURCE_DIR "/sources/1_1/input.txt";
    const string output_file = SOURCE_DIR "/sources/1_1/output.txt";
}

int main( int argc, char* argv[] )
{
    std::ifstream input_file( Paths::input_file );
    

    if ( !input_file.eof() )
    {
        std::string first_line;
        std::getline( input_file, first_line );

        while ( !input_file.eof() )
        {
            input_file >> first_line;

            std::getline( input_file, first_line );
            std::cout << first_line.c_str() << std::endl;
        }

    }


    input_file.close();
}
