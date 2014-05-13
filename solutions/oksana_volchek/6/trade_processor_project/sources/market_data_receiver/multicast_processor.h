#ifndef _MARKET_DATA_RECEIVER_MULTICAST_PROCESSOR_H_
#define _MARKET_DATA_RECEIVER_MULTICAST_PROCESSOR_H_

#include <vector>

#include "data_receiver.h"
#include "minute_calculator.h"
#include "thread_safe_queue.h"
#include "trade_message.h"
#include "quote_message.h"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace market_data_receiver
{
	class multicast_processor : private boost::noncopyable
	{
		typedef std::pair< std::string, unsigned short > multicast_pair;
		typedef boost::shared_ptr< multicast_communication::trade_message> trade_message_ptr;
		typedef queue::thread_safe_queue< trade_message_ptr > tr_queue;
		typedef boost::shared_ptr< tr_queue > trade_queue_ptr;
		typedef boost::shared_ptr< multicast_communication::quote_message > quote_message_ptr;
		typedef queue::thread_safe_queue< quote_message_ptr > qt_queue;
		typedef boost::shared_ptr< qt_queue > quote_queue_ptr;
		
		size_t trade_thread_size_;
		size_t quote_thread_size_;
		std::vector< multicast_pair > trade_ports_;
		std::vector< multicast_pair > quote_ports_;
		
		trade_queue_ptr trade_queue_;
		quote_queue_ptr quote_queue_;
		
		boost::shared_ptr< multicast_communication::data_receiver > data_receiver_obj_;
		boost::shared_ptr< minute_calculator::minute_calculator > minute_calculator_obj_;

		void read_config();

	public:
		explicit multicast_processor();
		~multicast_processor();
		void start();
	};
}

#endif // _MARKET_DATA_RECEIVER_MULTICAST_PROCESSOR_H_