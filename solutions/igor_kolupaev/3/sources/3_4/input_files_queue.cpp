#include "input_files_queue.h"

#include <sstream>
#include <iomanip>

#include <boost/algorithm/string/replace.hpp>

input_files_queue::input_files_queue(): _last_index( BEGIN_INDEX ) 
{
}

void input_files_queue::get_next( std::string& input_filename, std::string& output_filename )
{
	boost::mutex::scoped_lock lock( _queue_mutex );

	if( _last_index > END_INDEX )
	{
		throw std::out_of_range( "no more files are expected" );
	}

	std::ostringstream string_stream;

	string_stream << "input_";
	string_stream << std::fixed << std::setw( 3 ) << std::setfill( '0' );
	string_stream << _last_index++ << ".txt";

	input_filename = string_stream.str();
	output_filename = boost::replace_all_copy( input_filename, "input", "output" );
}
