#ifndef _TASK4_4_MESSAGE_READER_H_
#define _TASK4_4_MESSAGE_READER_H_

#include <fstream>
#include <vector>

#include <boost/noncopyable.hpp>

#include "message.h"

namespace task4_4
{
	typedef std::vector< message_ptr > messages;

	class message_reader : public boost::noncopyable
	{
		messages data_;
		std::ifstream input_file_;
	public:
		explicit message_reader( const std::string& file_name );
		void read_file();

		const messages& data() const;
	};
}

#endif // _TASK4_4_MESSAGE_READER_H_
