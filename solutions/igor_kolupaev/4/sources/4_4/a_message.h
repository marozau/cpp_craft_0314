#ifndef _TASK4_4_A_MESSAGE_H_
#define _TASK4_4_A_MESSAGE_H_

#include "message.h"

namespace task4_4
{
	class a_message : public message
	{
		static const size_t content_size = 16; 
		std::string content_;

		explicit a_message( std::istream& inp );
	public:
		static message_ptr create_message( std::istream& inp );
		~a_message();

		const char type() const;
		const std::string str() const;
	};

}

#endif // _TASK4_4_A_MESSAGE_H_

