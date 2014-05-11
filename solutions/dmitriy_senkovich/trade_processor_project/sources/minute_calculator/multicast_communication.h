#ifndef _MULTICAST_COMMUNICATION_H_
#define _MULTICAST_COMMUNICATION_H_

#include "udp_listener.h"
#include "market_data_processor.h"
#include "trade_message.h"
#include "quote_message.h"
#include <fstream>

namespace trade_processor_project
{
	struct market_data_processor;

	class multicast_communication
	{
		friend class udp_listener;

		typedef boost::shared_ptr< std::string > buffer_type;
		typedef std::pair< std::string, unsigned short > address;
		typedef boost::shared_ptr< boost::asio::io_service > io_service_ptr;
		
		static boost::thread_group listening_threads_;

	public:
		static boost::thread_group parsing_threads_;

	private:
		static std::vector< std::pair< io_service_ptr, udp_listener_ptr > > listeners_storage_;
		
		static std::ofstream output_;

		const char SOH;
		const char ETX;
		const char US;

		market_data_processor& processor_;
			 
		std::queue< buffer_type > trade_block_queue;
		std::queue< buffer_type > quote_block_queue;

	private:
		boost::mutex lock_output_;
	
		std::vector< address > trade_ports_;
		std::vector< address > quote_ports_;

		const size_t trade_thread_size_;
		const size_t quote_thread_size_;

		const size_t trade_ports_amount_;
		const size_t quote_ports_amount_;


	public:
		static bool to_stop;
		static boost::mutex lock_to_stop;
		explicit multicast_communication( const size_t, const size_t, const size_t, const size_t, const std::vector< address >&, const std::vector< address >&, market_data_processor& );
		void start();
		void make_new_message( const bool );
		void run_io_service( const io_service_ptr& );
		static void read_double( double&, std::stringstream&, const size_t );
		static void read_string( std::string&, std::stringstream&, const size_t );
		static void move_pos( std::stringstream&, const size_t );
		static void stop();
	};
}

#endif