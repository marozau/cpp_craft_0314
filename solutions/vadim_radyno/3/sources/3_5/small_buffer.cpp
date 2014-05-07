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
		const string begin_output_file_name = BINARY_DIR "/output_";
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
	explicit cMessagesReader(const int _count_messages)
	: m_message_counter(_count_messages)
	{
		createThreads();
	}

	void createThreads()
	{
		boost::thread_group group_of_slave_threads;
		static int count_threads = 4;

		for (int i = 1; i <= count_threads; ++i)
		{
			group_of_slave_threads.create_thread( boost::bind(&cMessagesReader::readMessage, this));
		}

		group_of_slave_threads.join_all();
	}

	void write(const tAttributies& _attrs, const int _message_index) const
	{
		const string& output_file_name = getPathToFileByIndex(Constants::Paths::begin_output_file_name, _message_index);
		std::ofstream output_file(output_file_name, std::ios::out | std::ios::binary);

		for (const auto& attr : _attrs)
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

	void readMessage()
	{
		while (true)
		{
			boost::mutex::scoped_lock lock_message_counter(m_counter_wait);			
			if (m_message_counter == 0)
			{
				break;
			}
			const int message_index = m_message_counter--;

			lock_message_counter.unlock();

			const string& path_to_message = getPathToFileByIndex(Constants::Paths::begin_input_file_name, message_index);

			std::ifstream input_file(path_to_message, std::ios::in | ios::binary);

			if (!input_file.is_open())
			{
				continue;
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

			if (!attrs.empty())
			{
				write(attrs, message_index);
			}

		}
	}

private:
	boost::mutex m_counter_wait;
	int m_message_counter;
};



int main()
{
    cMessagesReader messages_reader(Constants::count_files);
    return 0;
}

