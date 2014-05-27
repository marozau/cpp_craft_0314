#ifndef _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_


#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace multicast_communication{

	enum trade_type { SHORT_T, LONG_T };

	class trade_message;
	typedef boost::shared_ptr< trade_message > trade_message_ptr;

	namespace const_size_short_trade{
		static const size_t s_security_symbol = 3;
		static const size_t s_volume = 4;
		static const size_t s_price_den_ind = 1;
		static const size_t s_price = 8;
	}

	namespace const_size_long_trade{
		static const size_t s_security_symbol = 11;
		static const size_t s_volume = 9;
		static const size_t s_price_den_ind = 1;
		static const size_t s_price = 12;
	}

	class trade_message : public boost::enable_shared_from_this< trade_message >{
		private:
			

			typedef boost::function< void( const trade_message_ptr& ) > trade_callback_func;

			const bool test_;
			std::string security_symbol_;
			std::string	volume_;
			std::string	price_den_ind_;
			std::string	price_;
			std::string time_;

			void get (const std::string & str_from, std::string & str_to, const size_t len, size_t & it);
			const trade_callback_func call;
		public:
			explicit trade_message( const std::string & str, const trade_type t, const trade_callback_func c );
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
