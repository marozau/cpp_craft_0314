#include "trade_message.h"
#include <boost/lexical_cast.hpp>

namespace multicast_communication{

	trade_message::trade_message( const std::string & str, const trade_type t, const trade_callback_func c ): call( c ), test_(false){
	}

	trade_message::trade_message( const std::string & str, const trade_type t ): test_(true){
		segmentation (str, t);
	}

	trade_message::trade_message():
			test_(true),
			security_symbol_(""),
			volume_("0"),
			price_den_ind_("0"),
			price_("0"), 
			time_("0"){
	}

	std::string trade_message::security_symbol() const{
		return security_symbol_;
	}

	double trade_message::price() const{
		return boost::lexical_cast< double >( price_ );
	}

	double trade_message::volume() const{
		return boost::lexical_cast< double >( volume_ );
	}

	boost::uint32_t trade_message::minute() const{
		return ( time_[0]-'0' )*60 + ( time_[1]-'0' ) ;
	}

	void trade_message::segmentation(const std::string & str, const trade_type t ){
		size_t it = 16;
		get (str,time_,6,it);
		if(t == SHORT_T){
			using namespace const_size_short_trade;
			get(str, security_symbol_, s_security_symbol, it);
			++it;
			get(str, volume_, s_volume, it);
			get(str, price_den_ind_, s_price_den_ind , it);
			get(str, price_, s_price , it);
			it+=3;
		}
		else{
			using namespace const_size_long_trade;
			get(str, security_symbol_, s_security_symbol , it);
			it+=21;
			get(str, price_den_ind_, s_price_den_ind , it);
			get(str, price_, s_price , it);
			get(str, volume_, s_volume , it);
			it+=4;
		}
		if (!test_)
			call(shared_from_this() );
	}

	void trade_message::get (const std::string & str_from, std::string & str_to,const size_t len, size_t & it){
		if (it+len-1>str_from.length()) return;
		char * str = const_cast<char *>(str_from.c_str());
		str_from.copy(str, len, it);
		str_to = boost::lexical_cast<std::string>(str);
		str_to.resize(len);
		it+=len;
	}
}
