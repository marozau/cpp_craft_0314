#ifndef _MULTICAST_COMMUNICATION_SEPARATOR_H_
#define _MULTICAST_COMMUNICATION_SEPARATOR_H_


#include "main_processor.h"

#include <boost/function.hpp>

namespace multicast_communication{

	class separator{
		typedef boost::function< void( const trade_message_ptr & ) > trade_call;
		typedef boost::function< void( const quote_message_ptr & ) > quote_call;	
		private:
			const std::string message_;
			const message_type type_;
			const main_processor_ptr proc;


			const trade_call callback_t;
			const quote_call callback_q;

			static const char SOH = 0x01;
			static const char US = 0x1F;
			static const char ETX = 0x03;

			void block ();
		public:
			explicit separator(const std::string & str , const message_type mt, const main_processor_ptr p);

	};
	typedef boost::shared_ptr< separator > separator_ptr;

}

#endif //_MULTICAST_COMMUNICATION_SEPARATOR_H_