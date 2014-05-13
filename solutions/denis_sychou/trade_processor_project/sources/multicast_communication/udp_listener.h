#ifndef _ASYNC_UDP_UDP_LISTENER_H_
#define _ASYNC_UDP_UDP_LISTENER_H_

#include "market_processor.h"
#include "multicast_communication.h"

#include <string>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace multicast_communication
{
	class communication;

	namespace async_udp
	{
		class udp_listener : virtual private boost::noncopyable
		{
			static const size_t buffer_size;

			boost::asio::io_service& io_service_;

			boost::asio::ip::udp::endpoint listen_endpoint_;
			boost::asio::ip::udp::socket socket_;

			std::string multicast_address_;

			typedef boost::shared_ptr< std::string > buffer_type;

			buffer_type buffer;
			communication& callback_communication;
			const message_type client_type; 

			mutable boost::mutex protect_messages_;

		public:
			explicit udp_listener( boost::asio::io_service& io_service, const std::string& multicast_address, unsigned short port, communication& callback_communication, message_type client_type );
			~udp_listener();
		private:
			void socket_reload_();
			void register_listen_();
			void listen_handler_( buffer_type bt, const boost::system::error_code& error ); //, const size_t bytes_received );
		};
	}
}

#endif // _ASYNC_UDP_UDP_LISTENER_H_
