#ifndef _MULTICAST_COMMUNICATION_DATA_RECEIVER_H_
#define _MULTICAST_COMMUNICATION_DATA_RECEIVER_H_

#include <map>
#include <vector>
#include <fstream>

#include "market_data_processor.h"
#include "market_data_writer.h"
#include "udp_listener.h"
#include "thread_safe_queue.h"
#include "trade_message.h"
#include "quote_message.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

namespace multicast_communication
{
	class data_receiver : private boost::noncopyable
	{
		
		typedef std::pair< std::string, unsigned short > multicast_pair;
		
		typedef boost::shared_ptr< multicast_communication::trade_message> trade_message_ptr;
		typedef queue::thread_safe_queue< trade_message_ptr > tr_queue;
		typedef boost::shared_ptr< multicast_communication::quote_message > quote_message_ptr;
		typedef queue::thread_safe_queue< quote_message_ptr > qt_queue;
		typedef boost::shared_ptr< tr_queue > trade_queue_ptr;
		typedef boost::shared_ptr< qt_queue > quote_queue_ptr;
		typedef queue::thread_safe_queue< std::string > queue;

		const size_t trade_thread_size_;
		const size_t quote_thread_size_;
		std::vector<multicast_pair> trade_ports_;
		std::vector<multicast_pair> quote_ports_;
		
		queue string_trade_queue_;
		queue string_quote_queue_;

		trade_queue_ptr t_pointer_;
		quote_queue_ptr q_pointer_;

		boost::asio::io_service trade_service_;
		boost::asio::io_service quote_service_;
		std::list<boost::shared_ptr<async_udp::udp_listener> > listeners_;

		boost::thread_group processing_threads_;
		boost::thread_group gr_threads_;

		bool is_active_;
		std::ofstream output_;
		boost::shared_ptr<market_data_writer> processing_;
		boost::mutex mtx_;

		void listen(boost::asio::io_service & service, std::string & addr, unsigned short port, queue & res, char msg_type);
		void start(boost::asio::io_service & service);
		void block_split(queue & block_queue, char identifier);
		void stop();

	public:
		explicit data_receiver(size_t trade_thread_size, size_t quote_thread_size, std::vector<multicast_pair> & trade_ports, 
				std::vector<multicast_pair> & quote_ports, trade_queue_ptr & main_trade_queue, quote_queue_ptr & main_quote_queue);
		~data_receiver();
	};
}

#endif // _MULTICAST_COMMUNICATION_DATA_RECEIVER_H_