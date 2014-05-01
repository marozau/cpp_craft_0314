#include "quote_message.h"
#include "main_processor.h"

#include <boost\bind.hpp>
#include <boost\lexical_cast.hpp>


namespace multicast_communication{

	quote_message::quote_message(const std::string & str, const quote_type t, quote_callback_func c ):call( c ),test_(false){
	}

	quote_message::quote_message( const std::string & str, const quote_type t ):test_(true){
		segmentation (str, t);
	}

	quote_message::quote_message( ):test_(true),
									security_symbol_(""),
									bid_price_("0"),
									bid_price_den_ind_("0"),
									bid_size_of_units_of_trade_("0"),
									offer_price_("0"),
									offer_price_den_ind_("0"),
									offer_size_of_units_of_trade_("0"),
									lower_band_den_ind_("0"), 
									lower_band_("0"),
									bid_size_in_units_of_trade_("0"), 
									upper_band_den_ind_("0"),
									upper_band_("0"),
									offer_size_in_units_of_trade_("0"), 
									time_("0"){
	}

	std::string quote_message::security_symbol() const{
		return security_symbol_;
	}

	double quote_message::bid_price() const{
		return boost::lexical_cast< double >( bid_price_ );
	}

	double quote_message::bid_volume() const{
		return boost::lexical_cast< double >( bid_size_in_units_of_trade_ );
	}

	double quote_message::offer_price() const{
		return boost::lexical_cast< double >( offer_price_ );
	}

	double quote_message::offer_volume() const{
		return boost::lexical_cast< double >( offer_size_in_units_of_trade_ );
	}

	boost::uint32_t quote_message::minute() const{
		return ( time_[0]-'0' )*60 + ( time_[1]-'0' ) ;
	}

	
	void quote_message::segmentation( const std::string & str, const quote_type t ){
		size_t it = 16;
		get (str,time_,6,it);
		if (t == SHORT_Q){
			get(str, security_symbol_, 3, it);
			it+=3;
			get(str, bid_price_den_ind_, 1, it);
			get(str, bid_price_, 8, it);
			get(str, bid_size_in_units_of_trade_, 3, it);
			++it;
			get(str, offer_price_den_ind_, 1, it);
			get(str, offer_price_, 8, it);
			get(str, offer_size_in_units_of_trade_, 3, it);
			it+=3;
		}
		else
		if ( t == LONG_Q ){
			get(str, security_symbol_, 11, it);
			it+=16;
			get(str, lower_band_den_ind_, 1, it);
			get(str, bid_price_, 12, it);
			get(str, bid_size_in_units_of_trade_, 7, it);
			get(str, upper_band_den_ind_, 1, it);
			get(str, offer_price_, 12, it );
			get(str, offer_size_in_units_of_trade_, 7, it);
			it+=11;
		}
		if (!test_)
			call ( shared_from_this() );
	}

	void quote_message::get (const std::string & str_from, std::string & str_to,const size_t len, size_t & it){
		if (it+len-1>str_from.length()) return;
		char * str = const_cast<char *>(str_from.c_str());
		str_from.copy(str, len, it);
		str_to = boost::lexical_cast<std::string>(str);
		str_to.resize(len);
		it+=len;
	}

}
