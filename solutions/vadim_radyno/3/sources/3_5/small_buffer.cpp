#include "market_message.h"
#include <string>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <boost/thread.hpp>
#include <vector>


using namespace std;


namespace Constants
{
    namespace Paths
    {
        const string begin_input_file_name = BINARY_DIR "/input_";
        const string output_file = BINARY_DIR "/output.txt";
    }

    const int count_files = 999;
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


string getPathToFileByIndex(const string& _begin_path, const int _index)
{
    static const int index_size = 4;
    std::stringstream file_name;
    file_name << _begin_path;

    std::string input, output;
    char index_str[index_size];
    sprintf_s( index_str, index_size, "%03d", _index );
    file_name << index_str << ".txt";

    return file_name.str() ; 
}

class cMessagesReader final
{
public:
    explicit cMessagesReader(){}
    void readMessages()
    {
        boost::thread_group group_of_slave_threads;

        for (int i = 1; i <= Constants::count_files; ++i)
        {
            group_of_slave_threads.create_thread( boost::bind(&cMessagesReader::readMessage, this, i));
        }

        group_of_slave_threads.join_all();
    }

    void write()
    {
        std::ofstream output_file(Constants::Paths::output_file, std::ios::out | std::ios::binary);

        for (const auto& attr : m_attrs)
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

private:
    cMessagesReader(cMessagesReader&);
    cMessagesReader operator=(cMessagesReader&);

    void readMessage(const int _message_index)
    {
        const string& path_to_message = getPathToFileByIndex(Constants::Paths::begin_input_file_name, _message_index);

        std::ifstream input_file(path_to_message, std::ios::in | ios::binary);

        if (!input_file.is_open())
        {
            return;
        }

        while (!input_file.eof())
        {
            binary_reader::market_message message(input_file);

            if (input_file.eof())
            {
                break;
            }

            if (!message.isValidType())
            {
                continue;
            }

            boost::mutex::scoped_lock lock(m_wait);

            sMessagesAttributies& message_attributies = m_attrs[message.type()];

            const boost::uint32_t new_message_size = message_attributies.m_seconds_and_message_size[message.time()] + message.size();

            if (new_message_size <= Constants::max_message_size)
            {
                message_attributies.m_seconds_and_message_size[message.time()] = new_message_size;

                ++message_attributies.m_count;
            }
        }

        input_file.close();
    }

private:
    boost::mutex m_wait;
    tAttributies m_attrs;
};


int main()
{
    cMessagesReader messages_reader;

    messages_reader.readMessages();
    messages_reader.write();

    return 0;
}

