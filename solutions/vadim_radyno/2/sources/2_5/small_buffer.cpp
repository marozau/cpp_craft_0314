#include "market_message.h"
#include <string>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

namespace Constants
{
    namespace Paths
    {
        const string input_file = BINARY_DIR "/input.txt";
        const string output_file = BINARY_DIR "/output.txt";
    }
    const boost::int32_t max_message_size = 2048;
}

typedef set<boost::uint32_t> tSeconds;
typedef map<boost::uint32_t, boost::uint32_t> tSecondAndSize;



struct sMessagesAttributies
{
    sMessagesAttributies()
        : m_count(0)
    { }

    boost::uint32_t  m_count;
    tSecondAndSize   m_seconds_and_message_size;
};

typedef boost::uint32_t tTypeMessage;
typedef map<tTypeMessage, sMessagesAttributies> tAttributies;

int main()
{
    std::ifstream input_file(Constants::Paths::input_file, std::ios::in | ios::binary);

    if (!input_file.is_open())
    {
        return -1;
    }

    tAttributies attrs;
    while (!input_file.eof())
    {
        binary_reader::market_message message(input_file);

        if (input_file.eof())
        {
            break;
        }

        sMessagesAttributies& message_attributies = attrs[message.type()];

        const boost::uint32_t new_message_size = message_attributies.m_seconds_and_message_size[message.time()] + message.size();

        if (new_message_size <= Constants::max_message_size)
        {
            message_attributies.m_seconds_and_message_size[message.time()] = new_message_size;

            ++message_attributies.m_count;
        }
    }

    input_file.close();

    std::ofstream output_file(Constants::Paths::output_file, std::ios::out | std::ios::binary);
    
    for (const auto& attr : attrs)
    {
        const double mean = static_cast<double>(attr.second.m_count) / static_cast<double>(attr.second.m_seconds_and_message_size.size());
        if (mean != 0.0)
        {
            output_file.write(reinterpret_cast<const char*>(&(attr.first)), sizeof(attr.first));
            output_file.write(reinterpret_cast<const char*>(&(mean)), sizeof(mean));
        }
    }

    output_file.close();

}
