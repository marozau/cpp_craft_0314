#ifndef _MULTICAST_COMMUNICATION_COMMUNICATION_H_
#define _MULTICAST_COMMUNICATION_COMMUNICATION_H_

#include "thread_safe_queue.h"
#include "market_data_processor.h"
#include "udp_listener.h"
#include "main_processor.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include <vector>
#include <list>


namespace multicast_communication{

	namespace async_udp{
		class udp_listener;
	}

	class main_communication{

		typedef std::pair< std::string, unsigned short > IP_port;
		typedef boost::shared_ptr< boost::asio::io_service > service_ptr;

		private:

			bool end_;
			boost::mutex end_mtx_;


			const size_t trade_thread_size_;
			const size_t quote_thread_size_;

			const std::vector< IP_port >& trade_ports_;
			const std::vector< IP_port >& quote_ports_;

			std::vector <service_ptr> run_service_;

			std::list < boost::shared_ptr< async_udp::udp_listener > > all_listeners_;

			boost::thread_group quote_threads_;
			boost::thread_group trade_threads_;
			boost::thread_group link_threads_;

			thread_safe_queue< std::string > queue_t_;
			thread_safe_queue< std::string > queue_q_;

			main_processor_ptr processor_;

		private:

			void new_link( service_ptr io );
			void read();
			void pop_trade();
			void pop_quote();

		public:
	
			explicit main_communication (const size_t trade_thread_size,
										const size_t quote_thread_size,
										const std::vector< IP_port >& trade_ports,
										const std::vector< IP_port >& quote_ports,
										main_processor_ptr processor );

			~main_communication();

			void go();		
			void push_message( const std::string & m, const message_type t);

	};
}


#endif // _MULTICAST_COMMUNICATION_COMMUNICATION_H_