#include <iosfwd>
#include <string>

#include "market_message.h"
#include <xutility>
#include <iostream>

using namespace std;

namespace Constants
{
    namespace Paths
    {
        const string input_file = BINARY_DIR "/input.txt";
        const string output_file = BINARY_DIR "/output.txt";
    }
}


bool isValidTimeForMessage(const boost::uint32_t _max_time, const binary_reader::market_message& _message)
{
    static const boost::uint32_t time_delay = 2;

    return time_delay + _message.time() > _max_time;
}

int main()
{
    std::ifstream input_file(Constants::Paths::input_file, std::ios::in | ios::binary);

    if (!input_file.is_open())
    {
        return -1;
    }

    std::ofstream output_file(Constants::Paths::output_file, std::ios::out | std::ios::binary);
    boost::uint32_t max_time = 0;

    while (!input_file.eof())
    {
        binary_reader::market_message message(input_file);

        if (isValidTimeForMessage(max_time, message) && message.isValidType())
        {
            max_time = std::max(message.time(), max_time);
            message.write(output_file);
        }
    }

    output_file.close();
    input_file.close();
}

