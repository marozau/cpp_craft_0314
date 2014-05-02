#ifndef _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_


#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>


namespace multicast_communication{

	enum quote_type { SHORT_Q, LONG_Q };

	namespace const_size_short_quote{
		static const size_t s_security_symbol = 3;
		static const size_t s_bid_price_den_ind = 1;
		static const size_t s_bid_price = 8;
		static const size_t s_bid_size_in_units_of_trade = 3;
		static const size_t s_offer_price_den_ind = 1;
		static const size_t s_offer_price = 8;
		static const size_t s_offer_size_in_units_of_trade = 3;
	}

	namespace const_size_long_quote{
			static const size_t s_security_symbol = 11;
			static const size_t s_lower_band_den_ind = 1;
			static const size_t s_bid_price = 12;
			static const size_t s_bid_size_in_units_of_trade = 7;
			static const size_t s_upper_band_den_ind = 1;
			static const size_t s_offer_price = 12;
			static const size_t s_offer_size_in_units_of_trade = 7;
	}

	class quote_message;
	typedef boost::shared_ptr< quote_message > quote_message_ptr;


	class quote_message: public boost::enable_shared_from_this < quote_message >{
		private:
			const bool test_;
	
			std::string 
						bid_price_,
						bid_size_of_units_of_trade_,
						offer_price_,
						offer_size_in_units_of_trade_,
						time_;
			std::string 
						security_symbol_,
						bid_price_den_ind_,
						offer_price_den_ind_,
						offer_size_of_units_of_trade_,
						lower_band_den_ind_, 
						lower_band_,
						bid_size_in_units_of_trade_, 
						upper_band_den_ind_,
						upper_band_;

			typedef boost::function < void ( const quote_message_ptr & ) > quote_callback_func;
			const quote_callback_func call;
			void get (const std::string & str_from, std::string & str_to, const size_t len, size_t & it);

		public:

			explicit quote_message( const std::string & str, const quote_type t, const quote_callback_func c );
			explicit quote_message( const std::string & str, const quote_type t);
			explicit quote_message();

			std::string security_symbol() const;
			double bid_price() const;
			double bid_volume() const;
			double offer_price() const;
			double offer_volume() const;
			boost::uint32_t minute() const;

			void segmentation( const std::string & in, const quote_type t );
	};

}

#endif // _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
