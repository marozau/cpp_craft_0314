#pragma once

#include <string>
#include <boost/thread.hpp>

class input_files_queue
{
private:
	boost::mutex _queue_mutex;

	const static unsigned int BEGIN_INDEX = 1;
	const static unsigned int END_INDEX = 999;

	unsigned int _last_index;

public:

	input_files_queue();
	void get_next( std::string& input_filename, std::string& output_filename );
};

