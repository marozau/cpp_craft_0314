#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

namespace multicast_communication
{
	enum message_type { QUOTE, TRADE };

	enum quote_type { SHORT_Q, LONG_Q };

	namespace const_size_short_quote
	{
		static const size_t s_security_symbol = 3;
		static const size_t s_bid_price_den_ind = 1;
		static const size_t s_bid_price = 8;
		static const size_t s_bid_size_in_units_of_trade = 3;
		static const size_t s_offer_price_den_ind = 1;
		static const size_t s_offer_price = 8;
		static const size_t s_offer_size_in_units_of_trade = 3;
	}

	namespace const_size_long_quote
	{
		static const size_t s_security_symbol = 11;
		static const size_t s_lower_band_den_ind = 1;
		static const size_t s_bid_price = 12;
		static const size_t s_bid_size_in_units_of_trade = 7;
		static const size_t s_upper_band_den_ind = 1;
		static const size_t s_offer_price = 12;
		static const size_t s_offer_size_in_units_of_trade = 7;
	}
}
#endif //MESSAGE_TYPES