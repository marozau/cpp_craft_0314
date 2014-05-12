#ifndef _MULTICAST_COMMUNICATION_UDP_LISTENER_H_
#define _MULTICAST_COMMUNICATION_UDP_LISTENER_H_

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>

namespace multicast_communication 
{
    class udp_listener: virtual private boost::noncopyable
    {		
        public:
            typedef std::vector<char> message_type; 
            struct message
            {
                message_type data;
                enum TYPE
                {
                    TRADE,
                    QUOTE
                } type_;
            };
			typedef boost::function< void (message const&) > call_back_;

            typedef boost::shared_ptr< message_type > buffer_type;
            typedef std::pair<std::string, unsigned short> endpoint_addr;
            typedef boost::shared_ptr< boost::asio::ip::udp::endpoint > endpoint_ptr;
            typedef boost::shared_ptr< boost::asio::ip::udp::socket > socket_ptr;
            typedef boost::shared_ptr< udp_listener > udp_listener_ptr;

			udp_listener(const endpoint_addr addr, call_back_ func, const message::TYPE type, boost::asio::io_service& service );

            void socket_reload_();
            void register_listen_( buffer_type pre_buffer = buffer_type(), const size_t previous_size = 0 );
        private: 
            void listen_handler_( buffer_type bt, const boost::system::error_code& error, const size_t bytes_received );
            void enlarge_buffer_( buffer_type& bt );
            static const size_t default_buffer_size; 
            boost::asio::io_service& io_service_;
            call_back_ func_;
            endpoint_addr addr_;
            bool trade_type_;
            message::TYPE type_;
            socket_ptr socket_;
            endpoint_ptr endpoint_;
            boost::scoped_ptr< boost::thread > service_thread_;
    };
}

#endif
