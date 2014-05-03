#include "stock_data.h"

using namespace std;

namespace Constants
{
    namespace Paths
    {
        const string input_file = BINARY_DIR "/input.txt";
        const string output_file = BINARY_DIR "/output.txt";
    }
}

int main()
{
    std::ifstream input_file(Constants::Paths::input_file, std::ios::in | ios::binary);

    if (!input_file.is_open())
    {
        return -1;
    }

    std::ofstream output_file(Constants::Paths::output_file, std::ios::out | std::ios::binary);

    try
    {
        while (!input_file.eof())
        {
            binary_reader::stock_data message(input_file);
            message.write(output_file);
        }
    }
    catch(...)
    {

    }

    output_file.close();
    input_file.close();

    return 0;
}

