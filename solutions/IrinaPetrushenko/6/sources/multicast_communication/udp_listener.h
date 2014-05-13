#ifndef _ASYNC_UDP_UDP_LISTENER_H_
#define _ASYNC_UDP_UDP_LISTENER_H_

#include "communication.h"
#include "main_processor.h"

#include <string>
#include <vector>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace multicast_communication{

	class main_communication;

	namespace async_udp{

		class udp_listener{
			friend class main_communication;

			mutable boost::mutex protect_messages_;
			static const size_t default_buffer_size;

			boost::asio::io_service& io_service_;
			boost::asio::ip::udp::endpoint listen_endpoint_;
			boost::asio::ip::udp::socket socket_;

			std::string multicast_address_;

			typedef boost::shared_ptr< std::string > buffer_type;

			main_communication & com_;

			const multicast_communication::message_type client_type; 

			std::vector< std::string > messages_;

			public:
				explicit udp_listener( boost::asio::io_service& io_service,
										const std::string& multicast_address,
										main_communication & com,
										unsigned short port, 
										message_type client_type );
				~udp_listener();
				const std::vector< std::string > messages() const;
			private:
				void socket_reload_();
				void register_listen_( buffer_type pre_buffer = buffer_type(), const size_t previous_size = 0 );
				void listen_handler_( buffer_type bt, const boost::system::error_code& error, const size_t bytes_received );
				static void enlarge_buffer_( buffer_type& bt );
		};
	}
}

#endif // _ASYNC_UDP_UDP_LISTENER_H_