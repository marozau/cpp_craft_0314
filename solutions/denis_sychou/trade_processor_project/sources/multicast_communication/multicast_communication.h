#ifndef _MULTICAST_COMMUNICATION_MULTICAST_COMMUNICATION_H_
#define _MULTICAST_COMMUNICATION_MULTICAST_COMMUNICATION_H_


#include <vector>
#include <string>
#include <utility>

#include "thread_safe_queue.h"
#include "quote_message.h"
#include "trade_message.h"
#include "market_processor.h"
#include "udp_listener.h"

#include <boost\noncopyable.hpp>
#include <boost\thread.hpp>
#include <boost\asio.hpp>


namespace multicast_communication
{
	namespace async_udp
	{
		class udp_listener;
	}

	typedef boost::shared_ptr< boost::asio::io_service > io_service_ptr;
	typedef boost::shared_ptr< async_udp::udp_listener > udp_listener_ptr;
	typedef std::pair< std::string, unsigned short > address;
	typedef std::pair< io_service_ptr, boost::shared_ptr< async_udp::udp_listener > > connection;
		
	class communication : virtual private boost::noncopyable
	{
		const size_t trade_thread_size
				     , quote_thread_size;

		const std::vector< address > trade_ports, quote_ports;
		std::vector< connection > connections;

		boost::thread_group communication_threads, trade_threads, quote_threads;

		boost::mutex interrupt_mtx;

		task5_6::thread_safe_queue< std::string > quote_queue, trade_queue;

		bool interrupt;

		void process_trade();
		void process_quote();
		void connect( io_service_ptr io_service );

	public:
		processor_ptr processor;

		explicit communication( const size_t trade_thread_size_
								, const size_t quote_thread_size_
								, const std::vector< address > trade_ports_
								, const std::vector< address > quote_ports_
								, processor_ptr processor_ )
								: trade_thread_size( trade_thread_size_ )
								, quote_thread_size( quote_thread_size_ )
								, trade_ports( trade_ports_ )
								, quote_ports( quote_ports_ )
								, processor( processor_ )
								, interrupt( false )
		{ }
		~communication();
		void push_message( std::string& msg, message_type type );
		void start();
		void interruption();
	};

	typedef boost::shared_ptr< communication > communication_ptr;
}

#endif // _MULTICAST_COMMUNICATION_MULTICAST_COMMUNICATION_H_
