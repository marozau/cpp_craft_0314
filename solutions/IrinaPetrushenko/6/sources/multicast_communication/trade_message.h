#ifndef _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_


#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace multicast_communication{

	class trade_message;
	enum trade_type { SHORT_T, LONG_T };

	typedef boost::shared_ptr< trade_message > trade_message_ptr;
	typedef boost::function< void( const trade_message_ptr& ) > trade_callback_func;

	class trade_message : public boost::enable_shared_from_this< trade_message >{
		private:

			bool test_;
			std::string security_symbol_;
			std::string	volume_;
			std::string	price_den_ind_;
			std::string	price_;
			std::string time_;

			void get (const std::string & str_from, std::string & str_to, const size_t len, size_t & it);
			trade_callback_func call;
		public:
			explicit trade_message( const std::string & str, const trade_type t, trade_callback_func c );
			explicit trade_message( const std::string & str, const trade_type t);
			explicit trade_message ();
			std::string security_symbol() const;
			double price() const;
			double volume() const;
			boost::uint32_t minute() const;
			void segmentation(const std::string & in, const trade_type t );
	};

}

#endif // _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
