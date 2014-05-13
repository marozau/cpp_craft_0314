#ifndef _MINUTE_CALCULATOR_MINUTE_CALCULATOR_H_
#define _MINUTE_CALCULATOR_MINUTE_CALCULATOR_H_

#include <boost/cstdint.hpp>
#include <map>
#include <string>
#include <fstream>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#include "thread_safe_queue.h"
#include "trade_message.h"
#include "quote_message.h"

namespace minute_calculator {
		
	struct minute_datafeed {
		double open_price;
		double high_price;
		double low_price;
		double close_price;
		double volume;
		double bid;
		double offer;
		bool currently_is_active;
	};

	typedef boost::shared_ptr< multicast_communication::trade_message> trade_message_ptr;
	typedef queue::thread_safe_queue< trade_message_ptr > tr_queue;
	typedef boost::shared_ptr< multicast_communication::quote_message > quote_message_ptr;
	typedef queue::thread_safe_queue< quote_message_ptr > qt_queue;
	typedef boost::shared_ptr< tr_queue > trade_queue_ptr;
	typedef boost::shared_ptr< qt_queue > quote_queue_ptr;

	class minute_calculator : private boost::noncopyable 
	{	
		trade_queue_ptr t_pointer_;
		quote_queue_ptr q_pointer_;
		std::map<std::string, minute_datafeed> datafeed_;
		boost::uint32_t current_time_;
		bool is_active_;
		boost::mutex q_mtx_;
		boost::mutex t_mtx_;
		boost::thread_group threads_;

		void process_trade_msg();
		void process_quote_msg();
		void init_stockname(std::string s);
		void print_datafeed();
		void clear_datafeed();
		void start();

		public:
			explicit minute_calculator(trade_queue_ptr & main_trade_queue, quote_queue_ptr & main_quote_queue);
			~minute_calculator();
			const boost::uint32_t get_current_time() const;
			void stop();

	};
}
#endif // _MINUTE_CALCULATOR_MINUTE_CALCULATOR_H_