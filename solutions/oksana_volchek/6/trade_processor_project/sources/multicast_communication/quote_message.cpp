#include "quote_message.h"
#include "consts.h"
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/time_clock.hpp>

multicast_communication::quote_message::quote_message(const std::string & one_msg) :
						qt_security_symbol_ (""), qt_bid_price_ (0.0), qt_bid_volume_ (0.0), 
						qt_offer_price_ (0.0), qt_offer_volume_ (0.0), qt_hours_ (0), qt_minutes_ (0) 
{
	if (consts::types::qt_correct_category.count(one_msg[0])){
		if (consts::types::qt_correct_type.at(one_msg[1]) == 's' && one_msg.length() >= consts::qt_field_length::short_msg_length){
			multicast_communication::quote_message::init_short_qt_msg(one_msg);
		}
		else if (consts::types::qt_correct_type.at(one_msg[1]) == 'l' && one_msg.length() >= consts::qt_field_length::long_msg_length){
			multicast_communication::quote_message::init_long_qt_msg(one_msg);
		}
	}
}

multicast_communication::quote_message::quote_message() :
						qt_security_symbol_ (""), qt_bid_price_ (0.0), qt_bid_volume_ (0.0),
						qt_offer_price_ (0.0), qt_offer_volume_ (0.0), qt_hours_ (0), qt_minutes_ (0)
{

}

multicast_communication::quote_message::~quote_message() {

}

void multicast_communication::quote_message::init_short_qt_msg(const std::string & one_msg){
	qt_security_symbol_ = multicast_communication::quote_message::delete_spaces(one_msg.substr(consts::qt_start_field::start_sec_symbol, consts::qt_field_length::short_sec_symbol_length));
	qt_bid_volume_ = boost::lexical_cast<double> (one_msg.substr(consts::qt_start_field::start_short_bid_volume, consts::qt_field_length::short_bid_volume_length));
	qt_bid_price_ = get_price(consts::qt_start_field::start_short_bid_denominator, 
			consts::qt_start_field::start_short_bid_price, consts::qt_field_length::short_bid_price_length, one_msg);
	qt_offer_volume_ = boost::lexical_cast<double> (one_msg.substr(consts::qt_start_field::start_short_offer_volume, consts::qt_field_length::short_offer_volume_length));
	qt_offer_price_ = get_price(consts::qt_start_field::start_short_offer_denominator, consts::qt_start_field::start_short_offer_price, 
			consts::qt_field_length::short_offer_price_length, one_msg);
	multicast_communication::quote_message::get_time(one_msg);
}

void multicast_communication::quote_message::init_long_qt_msg(const std::string & one_msg){
	qt_security_symbol_ = multicast_communication::quote_message::delete_spaces(one_msg.substr(consts::qt_start_field::start_sec_symbol, consts::qt_field_length::long_sec_symbol_length));
	qt_bid_volume_ = boost::lexical_cast<double> (one_msg.substr(consts::qt_start_field::start_long_bid_volume, consts::qt_field_length::long_bid_volume_length));
	qt_bid_price_ = get_price(consts::qt_start_field::start_long_bid_denominator, 
			consts::qt_start_field::start_long_bid_price, consts::qt_field_length::long_bid_price_length, one_msg);
	qt_offer_volume_ = boost::lexical_cast<double> (one_msg.substr(consts::qt_start_field::start_long_offer_volume, consts::qt_field_length::long_offer_volume_length));
	qt_offer_price_ = get_price(consts::qt_start_field::start_long_offer_denominator, consts::qt_start_field::start_long_offer_price, 
			consts::qt_field_length::long_offer_price_length, one_msg);	
	multicast_communication::quote_message::get_time(one_msg);
}

std::string multicast_communication::quote_message::delete_spaces(const std::string & str){
	size_t len = 0;
	for(std::string::const_iterator iter = str.begin() ; iter != str.end(); ++iter){
		if (*iter != ' '){
			++len;
		}
		else {
			break;
		}
	}
	std::string new_str = str.substr(0, len);
	return new_str;
}

double multicast_communication::quote_message::get_price(const size_t start_pos_den, const size_t start_pos_price, const size_t price_len, const std::string & one_msg){
	const char key_denominator = boost::lexical_cast <char> (one_msg.substr(start_pos_den, 1));
	const size_t denominator = consts::convert_data::denominators.at(key_denominator);
	double tmp_price = boost::lexical_cast <double> (one_msg.substr(start_pos_price, price_len));
	if (denominator == 0){ 
		return 0.0; 
	}
	return (tmp_price / denominator);
}

void multicast_communication::quote_message::get_time(const std::string & one_msg){
	const std::string tmp_time = one_msg.substr(consts::tr_start_field::start_time, consts::tr_field_length::time_length);
	qt_hours_ = consts::convert_data::time_stamp.at(tmp_time[0]);
	qt_minutes_ = consts::convert_data::time_stamp.at(tmp_time[1]);
	const boost::gregorian::date today(boost::date_time::second_clock< boost::posix_time::ptime >::universal_time().date()); 
	boost::posix_time::ptime current_moment(today, boost::posix_time::time_duration(qt_hours_, qt_minutes_, 0));
	qt_time_ = (current_moment - consts::convert_data::initial_moment).total_seconds();
}

const std::string multicast_communication::quote_message::security_symbol() const {
	return qt_security_symbol_;
}

const double multicast_communication::quote_message::bid_price() const {
	return qt_bid_price_;
}

const double multicast_communication::quote_message::bid_volume() const {
	return qt_bid_volume_;
}

const double multicast_communication::quote_message::offer_price() const {
	return qt_offer_price_;
}

const double multicast_communication::quote_message::offer_volume() const {
	return qt_offer_volume_;
}

const boost::uint32_t multicast_communication::quote_message::minutes() const {
	return qt_minutes_;
}

const boost::uint32_t multicast_communication::quote_message::hours() const {
	return qt_hours_;
}

const boost::uint32_t multicast_communication::quote_message::time() const {
	return qt_time_;
}