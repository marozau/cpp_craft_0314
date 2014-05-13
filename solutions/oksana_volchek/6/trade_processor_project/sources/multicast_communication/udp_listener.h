#ifndef _ASYNC_UDP_UDP_LISTENER_H_
#define _ASYNC_UDP_UDP_LISTENER_H_

#include <string>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "thread_safe_queue.h"

namespace async_udp
{
	class udp_listener : virtual private boost::noncopyable
	{
		typedef boost::shared_ptr< std::string > buffer_type;

		static const size_t default_buffer_size;

		boost::asio::io_service & io_service_;
		boost::asio::ip::udp::endpoint listen_endpoint_;
		boost::asio::ip::udp::socket socket_;

		std::string multicast_address_;
		queue::thread_safe_queue<std::string>* messages_;
		boost::mutex protect_messages_;

	public:
		explicit udp_listener( boost::asio::io_service& io_service, const std::string & multicast_address, unsigned short port, 
			queue::thread_safe_queue<std::string> & vec);
		~udp_listener();
		queue::thread_safe_queue<std::string> & messages();
	private:
		void socket_reload_();
		void register_listen_( buffer_type pre_buffer = buffer_type(), const size_t previous_size = 0 );
		void listen_handler_( buffer_type bt, const boost::system::error_code& error, const size_t bytes_received );
		static void enlarge_buffer_( buffer_type & bt );
	};
}

#endif // _ASYNC_UDP_UDP_LISTENER_H_
