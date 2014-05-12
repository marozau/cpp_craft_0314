#include "market_data_writer.h"

multicast_communication::market_data_writer::market_data_writer(std::ofstream & out) : out_ (out) {

}

multicast_communication::market_data_writer::~market_data_writer() {

}

void multicast_communication::market_data_writer::new_trade( const trade_message_ptr& msg) {
	out_ << std::fixed << "T" << " " << msg->security_symbol() << " "
		<< std::setprecision(2) << msg->price() << " "
		<< std::setprecision(1) << msg->volume() << std::endl;
}


void multicast_communication::market_data_writer::new_quote( const quote_message_ptr & msg) {
	out_ << std::fixed << "Q" << " " << msg->security_symbol() << " "
		<< std::setprecision(2) << msg->bid_price() << " "
		<< std::setprecision(1) << msg->bid_volume() << " " 
		<< std::setprecision(2) << msg->offer_price() << " "
		<< std::setprecision(1) << msg->offer_volume() << std::endl;	
}