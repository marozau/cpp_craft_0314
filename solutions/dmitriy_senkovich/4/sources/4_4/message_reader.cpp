#include "message_reader.h"

#include <string>
#include <stdexcept>

#include "a_message.h"
#include "b_message.h"

task4_4::message_reader::message_reader( const std::string& filename )
{
	input_file_.open( filename.c_str() );
	if ( !input_file_.is_open() )
		throw std::logic_error( "input file '" + filename + "' can't be opened" );
}

void task4_4::message_reader::read_file()
{
	while ( !input_file_.eof() )
	{
		char type = 0;
		input_file_ >> type;
		if ( input_file_.eof() )
			break;

		switch( type )
		{
		case 'A': 
			data_.push_back( a_message::create_message( input_file_ ) );
			break;
		case 'B':
			data_.push_back( b_message::create_message( input_file_ ) );
			break;
		default:
			throw std::logic_error( "input file store unknown message type: " + type );
		}
	}
}

const task4_4::messages& task4_4::message_reader::data() const
{
	return data_;
}
