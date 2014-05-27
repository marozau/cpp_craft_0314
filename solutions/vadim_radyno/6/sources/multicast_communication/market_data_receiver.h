#ifndef _MULTICAST_COMMUNICATION_MARKET_DATA_RECEIVER_H_
#define _MULTICAST_COMMUNICATION_MARKET_DATA_RECEIVER_H_

#include <vector>
#include <string>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>

#include "thread_safe_queue.h" 
#include "market_data_processor.h"
#include "udp_listener.h"

namespace multicast_communication 
{
    class market_data_receiver : virtual protected boost::noncopyable
    {
		typedef std::vector<udp_listener::endpoint_addr> addreses_and_ports_;
		typedef  std::vector< udp_listener::udp_listener_ptr > udp_listeners_cont;
        public: 
			market_data_receiver( const size_t trade_thread_size, const size_t quote_thread_size, const addreses_and_ports_& trade_ports, const addreses_and_ports_& quote_ports, market_data_processor& processor) ;

            virtual ~market_data_receiver();

            void start(); 
            void stop(); 
            void join();
            size_t trades_size() const;
            size_t quotes_size() const;
            friend class udp_listener;
        private:
            boost::asio::io_service io_service_;

            thread_safe_queue< message_type > trade_queue_;
            mutable boost::mutex protect_trade_queue_;
            thread_safe_queue< message_type > quote_queue_;
            mutable boost::mutex protect_quote_queue_;

            boost::thread_group t_group_; 

			const size_t trade_thread_size_;
			const size_t quote_thread_size_;

            void process_trades_();
            void process_quotes_();

            virtual void receive( const udp_listener::message& mess);

            udp_listeners_cont listeners_; 

            market_data_processor& processor_; 

            bool stop_;
    };
}
#endif
