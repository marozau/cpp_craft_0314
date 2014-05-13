#ifndef _ASYNC_UDP_UDP_LISTENER_H_
#define _ASYNC_UDP_UDP_LISTENER_H_

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <queue>

namespace trade_processor_project
{
	class udp_listener : virtual private boost::noncopyable
	{
		typedef boost::shared_ptr< std::string > buffer_type;
		typedef boost::shared_ptr< boost::asio::io_service > io_service_ptr;

		static const size_t default_buffer_size = 1000ul;

		const bool trade_;

		std::queue< buffer_type >& block_message_queue_;

		buffer_type buffer_;

		boost::asio::io_service& io_service_;

		boost::asio::ip::udp::endpoint listen_endpoint_;
		boost::asio::ip::udp::socket socket_;

		std::string multicast_address_;

	public:
		static bool to_stop;
		static boost::mutex lock_to_stop;
		static boost::mutex lock_trade_queue_;
		static boost::mutex lock_quote_queue_;
		static boost::condition_variable trade_cond_var_;
		static boost::condition_variable quote_cond_var_;
		explicit udp_listener( boost::asio::io_service&, const std::string&, unsigned short, bool, std::queue< buffer_type >& );
		std::queue< buffer_type >& messages();
	private:
		void socket_reload_();
		void register_listen_();
		void listen_handler_( buffer_type, const boost::system::error_code&, const size_t );
	};
	typedef boost::shared_ptr< udp_listener > udp_listener_ptr;
}

#endif
