#ifndef _LISTENER_
#define _LISTENER_

#include "message_types.h"
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/signals2.hpp>

namespace multicast_communication
{
	
	class listener
	{
		static const size_t default_buffer_size;

		std::string ip;
		unsigned short port;
		message_type type;

		boost::asio::io_service io_service_;
		boost::asio::ip::udp::endpoint listen_endpoint_;
		boost::asio::ip::udp::socket socket_;
		
		boost::signals2::signal<void(std::string, message_type)> Raise;

		typedef boost::shared_ptr< std::string > buffer_type;
		void socket_reload();
		void register_listener(buffer_type pre_buffer = buffer_type(), const size_t previous_size = 0);
		void listen_handler_(buffer_type bt, const boost::system::error_code& error, const size_t bytes_received);
		static void enlarge_buffer_(buffer_type& bt);

	public:
		listener(std::string ip, unsigned short port, message_type type);
		void Start();
		void Stop();

		void AddHandler(boost::function<void(std::string, message_type)>);
	};
}
#endif //_LISTENER_