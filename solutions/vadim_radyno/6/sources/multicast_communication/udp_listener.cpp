#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "udp_listener.h"

namespace multicast_communication 
{ 
	udp_listener::udp_listener(const endpoint_addr addr, call_back_ func, const message::TYPE type, boost::asio::io_service& service) 
		: io_service_(service),
          func_(func), 
          addr_(addr), 
          type_(type)
	{
        socket_.reset(new boost::asio::ip::udp::socket( boost::ref( io_service_ ) ) );
        endpoint_.reset(new boost::asio::ip::udp::endpoint( boost::asio::ip::address::from_string( "0.0.0.0" ), addr.second ));
    }

    void udp_listener::socket_reload_()
    {
        using boost::asio::ip::udp;
        using boost::asio::ip::address;
        using boost::asio::ip::multicast::join_group;

        socket_->open( endpoint_->protocol() );
        socket_->set_option( udp::socket::reuse_address( true ) );
        socket_->bind( *endpoint_ );
        socket_->set_option( join_group( address::from_string( addr_.first ) ) );
    }

    void udp_listener::register_listen_( buffer_type pre_buffer, const size_t previous_size )
    {

        buffer_type buffer;

        if( pre_buffer )
            buffer = pre_buffer;
        else
            buffer.reset( new message_type( default_buffer_size, '\0' ) );

        char* const buffer_start = &(*buffer->begin());

        using namespace boost::asio::placeholders;
        socket_->async_receive( boost::asio::buffer( buffer_start, previous_size + default_buffer_size ),
                boost::bind( &udp_listener::listen_handler_, this, buffer, error, bytes_transferred ) );
    }

    void udp_listener::listen_handler_( buffer_type bt, const boost::system::error_code& error, const size_t bytes_received )
    {
        if ( error )
        {
            static const int NO_ENOUGHT_BUFFER = 234;
            if ( error.value() == NO_ENOUGHT_BUFFER )
            {
                enlarge_buffer_( bt );
                register_listen_( bt, bytes_received );
            }
            return;
        }
        if ( bytes_received == bt->size() && (*bt)[ bytes_received - 1 ] != '\0' )
        {
            enlarge_buffer_( bt );
            register_listen_( bt, bytes_received );
        }
        else
        {
            message_type data( bt->begin(), bt->begin() + bytes_received );
            message m;
            m.data = data;
            m.type_ = type_;
            func_(m);
            this->register_listen_( );
        }
    }

    void udp_listener::enlarge_buffer_( buffer_type& bt )
    {
        bt->resize( bt->size() + default_buffer_size );
    }

    const size_t udp_listener::default_buffer_size = 1000ul;

}
