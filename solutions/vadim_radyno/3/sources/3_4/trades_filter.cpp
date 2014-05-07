#include "market_message.h"
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <sstream>
#include <set>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>

using namespace std;

namespace Constants
{
    namespace Paths
    {
        const string begin_input_file_name = BINARY_DIR "/input_";
        const string begin_output_file_name = BINARY_DIR "/output_";
    }

    const int count_files = 999;
    const int index_size = 4;
}

bool isValidTimeForMessage(const boost::uint32_t _max_time, const binary_reader::market_message& _message)
{
    static const boost::uint32_t time_delay = 2;

    return time_delay + _message.time() > _max_time;
}

string getPathToFileByIndex(const string& _begin_path, const int _index)
{
    std::stringstream file_name;
    file_name << _begin_path;

    std::string input, output;
    char index_str[Constants::index_size];
    sprintf_s( index_str, Constants::index_size, "%03d", _index );
    file_name << index_str << ".txt";

    return file_name.str() ; 
}

class cProcessorMessage final
{
    typedef deque<int> tIndexFiles;

public:
    cProcessorMessage (const int _count_files)
        : m_is_run_threads(true)
        , m_file_counter(_count_files)
    {
        for (int i = 0; i < ms_count_thread; ++i)
        {
            m_group_of_slave_threads.create_thread(boost::bind( &cProcessorMessage::process, this));
        }
    }

    void stopAndWaitThread()
    {
        m_is_run_threads = false;
        m_group_of_slave_threads.join_all();
    }

private:
    cProcessorMessage(cProcessorMessage&);
    cProcessorMessage& operator=(cProcessorMessage&);

    void process()
    {
        while (true)
        {
            boost::mutex::scoped_lock files_lock(m_wait_files);

            if (m_file_counter != 0)
            {
                const int index_of_file = m_file_counter--;

                files_lock.unlock();

                const string& input_file_name = getPathToFileByIndex(Constants::Paths::begin_input_file_name, index_of_file);
                const string& output_file_name = getPathToFileByIndex(Constants::Paths::begin_output_file_name, index_of_file);


				std::ifstream input_file(input_file_name, std::ios::in | ios::binary);
				
				if (!input_file.is_open())
				{
					continue;
				}
				
				std::ofstream output_file(output_file_name, std::ios::out | std::ios::binary);
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
            else
            {
                return;
            }
        }
    }

private:
    boost::thread_group m_group_of_slave_threads;
    boost::mutex m_wait_files;
    bool m_is_run_threads;
    int  m_file_counter;

    static const int ms_count_thread    = 4;
};



int main()
{
    cProcessorMessage processor(Constants::count_files);
    processor.stopAndWaitThread();

    return 0;
}

