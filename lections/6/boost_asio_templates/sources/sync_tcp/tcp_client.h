#ifndef _SYNC_TCP_TCP_CLIENT_H_
#define _SYNC_TCP_TCP_CLIENT_H_

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

namespace sync_tcp
{
	class tcp_client : virtual public boost::noncopyable
	{
		boost::asio::io_service io_service_;
		boost::asio::ip::tcp::socket socket_;
	public:
		explicit tcp_client( const std::string& ip_address, const unsigned short port );
		void read( char* const data, const size_t size );
		void write( const char* const data, const size_t size );

		template< typename D >
		void read( D* const data, const size_t size );

		template< typename D >
		void write( const D* const data, const size_t size );
	};
}

template< typename D >
void sync_tcp::tcp_client::read( D* const data, const size_t size )
{
	read( reinterpret_cast< char* const >( data ), size );
}
template< typename D >
void sync_tcp::tcp_client::write( const D* const data, const size_t size )
{
	write( reinterpret_cast< const char* const >( data ), size );
}

#endif // _SYNC_TCP_TCP_CLIENT_H_
