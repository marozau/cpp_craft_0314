#include "trade_message.h"
#include "consts.h"
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/time_clock.hpp>

multicast_communication::trade_message::trade_message() : 
				tr_security_symbol_ (""), tr_price_ (0.0), tr_volume_ (0.0), tr_hours_ (0), tr_minutes_ (0)
{

}

multicast_communication::trade_message::trade_message(const std::string & one_msg) : 
				tr_security_symbol_ (""), tr_price_ (0.0), tr_volume_ (0.0), tr_hours_ (0), tr_minutes_ (0)
{
	if (one_msg.length() == consts::tr_field_length::long_msg_length){
		multicast_communication::trade_message::init_long_tr_msg(one_msg);
	}
	else if (one_msg.length() == consts::tr_field_length::short_msg_length){
		multicast_communication::trade_message::init_short_tr_msg(one_msg);
	}
}

multicast_communication::trade_message::~trade_message() {
}

void multicast_communication::trade_message::init_short_tr_msg(const std::string & one_msg){
	if (consts::types::tr_correct_category.count(one_msg[0]) && consts::types::tr_correct_type.count(one_msg[1])){
		tr_security_symbol_ = multicast_communication::trade_message::delete_spaces(one_msg.substr(consts::tr_start_field::start_sec_symbol, consts::tr_field_length::short_sec_symbol_length));
		tr_volume_ = boost::lexical_cast<double> (one_msg.substr(consts::tr_start_field::start_short_volume, consts::tr_field_length::short_volume_length));
		
		const char key_denominator = boost::lexical_cast<char> (one_msg.substr(consts::tr_start_field::start_short_denominator, 1));
		const size_t denominator = consts::convert_data::denominators.at(key_denominator);
		double tmp_price = boost::lexical_cast<double> (one_msg.substr(consts::tr_start_field::start_short_price, consts::tr_field_length::short_price_length));
		tr_price_ = tmp_price / denominator;

		multicast_communication::trade_message::get_time(one_msg);
	}
}
		
void multicast_communication::trade_message::init_long_tr_msg(const std::string & one_msg){
	if (consts::types::tr_correct_category.count(one_msg[0]) && consts::types::tr_correct_type.count(one_msg[1])){
		tr_security_symbol_ = multicast_communication::trade_message::delete_spaces(one_msg.substr(consts::tr_start_field::start_sec_symbol, consts::tr_field_length::long_sec_symbol_length));
		tr_volume_ = boost::lexical_cast<double> (one_msg.substr(consts::tr_start_field::start_long_volume, consts::tr_field_length::long_volume_length));
		
		const char key_denominator = boost::lexical_cast<char> (one_msg.substr(consts::tr_start_field::start_long_denominator, 1));
		const size_t denominator = consts::convert_data::denominators.at(key_denominator);
		double tmp_price = boost::lexical_cast<double> (one_msg.substr(consts::tr_start_field::start_long_price, consts::tr_field_length::long_price_length));
		tr_price_ = tmp_price / denominator;

		multicast_communication::trade_message::get_time(one_msg);
	}
}

void multicast_communication::trade_message::get_time(const std::string & one_msg) {
	const std::string tmp_time = one_msg.substr(consts::tr_start_field::start_time, consts::tr_field_length::time_length);
	tr_hours_ = consts::convert_data::time_stamp.at(tmp_time[0]);
	tr_minutes_ = consts::convert_data::time_stamp.at(tmp_time[1]);
	const boost::gregorian::date today(boost::date_time::second_clock< boost::posix_time::ptime >::universal_time().date()); 
	boost::posix_time::ptime current_moment(today, boost::posix_time::time_duration(tr_hours_, tr_minutes_, 0));
	tr_time_ = (current_moment - consts::convert_data::initial_moment).total_seconds();
}

std::string multicast_communication::trade_message::delete_spaces(const std::string & str){
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

const std::string multicast_communication::trade_message::security_symbol() const {
	return tr_security_symbol_;
}

const double multicast_communication::trade_message::price() const {
	return tr_price_;
}

const double multicast_communication::trade_message::volume() const {
	return tr_volume_;
}

const boost::uint32_t multicast_communication::trade_message::hours() const {
	return tr_hours_;
}

const boost::uint32_t multicast_communication::trade_message::minutes() const {
	return tr_minutes_;
}

const boost::uint32_t multicast_communication::trade_message::time() const {
	return tr_time_;
}