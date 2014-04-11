#ifndef _ASYNC_TCP_TCP_SERVER_H_
#define _ASYNC_TCP_TCP_SERVER_H_

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

namespace async_tcp
{
	struct client_manager;	
	class tcp_server : protected boost::noncopyable
	{
		boost::asio::io_service service_;
		boost::asio::ip::tcp::acceptor acc_;
		
	public:		
		typedef boost::shared_ptr< client_manager > client_ptr;

	private:
		typedef std::list< client_ptr > clients;
		clients clients_;
		boost::thread service_thread_;

	public:
		explicit tcp_server( const unsigned short port );
		~tcp_server();
		//
	private:
		void wait_for_connection_();
		void handle_accept_( const boost::system::error_code& er );
		void on_read_length_( client_ptr& cm, const boost::system::error_code& er );
		void on_read_( client_ptr& cm, const boost::system::error_code& er );
		void on_write_length_( client_ptr& cm, const boost::system::error_code& er );
		void on_write_( client_ptr& cm, const boost::system::error_code& er );
		//
		void run_service_();
	};
	struct client_manager : boost::noncopyable
	{
		typedef boost::shared_ptr< boost::asio::ip::tcp::socket > socket_ptr;
		size_t message_length_;
		char* buffer_;
		socket_ptr socket_;

	public:
		explicit client_manager( boost::asio::io_service& service )
			: message_length_( 0 )
			, buffer_( NULL )
		{
			using namespace boost::asio::ip;
			socket_.reset( new tcp::socket( service ) );
		}
		char* get_buffer()
		{
			delete [] buffer_;
			buffer_ = new char[ message_length_ ];
			return buffer_;
		}
		~client_manager()
		{
			socket_->close();
			delete [] buffer_;
		}
	};
}

#endif // _ASYNC_TCP_TCP_SERVER_H_
