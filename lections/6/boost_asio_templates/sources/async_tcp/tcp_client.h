#ifndef _ASYNC_TCP_TCP_CLIENT_H_
#define _ASYNC_TCP_TCP_CLIENT_H_

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>


namespace async_tcp
{
	class tcp_client;
	class tcp_client_manager
	{
		friend class tcp_client;
		char* buffer_;

	public:
		explicit tcp_client_manager();		
		virtual ~tcp_client_manager();		
		char* get_buffer( const size_t size );		
		virtual void message_read() = 0;
		virtual void message_sent() = 0;		
	};
	class tcp_client : protected boost::noncopyable
	{
		tcp_client_manager& manager_;
		boost::asio::io_service io_service_;
		boost::asio::ip::tcp::socket socket_;

		boost::thread service_;

		size_t length_;

	public:
		explicit tcp_client( tcp_client_manager& manager, const std::string& ip_address, const unsigned short port );
		~tcp_client();

		void write( const char* const data, const size_t size );

	private:
		void read_string_length_handler_( const boost::system::error_code& er );
		void read_string_handler_( const boost::system::error_code& er );
		//
		void write_string_handler_( const boost::system::error_code& er );
		//
		void run_service_();
	};
}

#endif // _ASYNC_TCP_TCP_CLIENT_H_
