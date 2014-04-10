#ifndef _SYNC_TCP_TCP_SERVER_H_
#define _SYNC_TCP_TCP_SERVER_H_

#include <list>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace sync_tcp
{
	class tcp_server : virtual public boost::noncopyable
	{
		boost::asio::io_service io_service_;
		boost::asio::ip::tcp::acceptor acceptor_;
		//
	public:
		typedef boost::shared_ptr< boost::asio::ip::tcp::socket > client_socket;
	private:
		typedef std::list< client_socket > sockets;
		sockets client_sockets_;
	public:
		explicit tcp_server( const unsigned short port );
		~tcp_server();
		client_socket wait_for_connection();

		void read( client_socket&, char* const data, const size_t size );
		void write( client_socket&, const char* const data, const size_t size );

		template< typename D >
		void read( client_socket&, D* const data, const size_t size );

		template< typename D >
		void write( client_socket&, const D* const data, const size_t size );

	};
}

template< typename D >
void sync_tcp::tcp_server::read( client_socket& socket, D* const data, const size_t size )
{
	read( socket, reinterpret_cast< char* const >( data ), size );
}
template< typename D >
void sync_tcp::tcp_server::write( client_socket& socket, const D* const data, const size_t size )
{
	write( socket, reinterpret_cast< const char* const >( data ), size );
}

#endif // _SYNC_TCP_TCP_SERVER_H_
