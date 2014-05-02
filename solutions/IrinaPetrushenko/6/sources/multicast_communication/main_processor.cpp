#include "main_processor.h"

#include <boost\lexical_cast.hpp>
#include <boost\bind.hpp>

namespace multicast_communication{

	main_processor::main_processor( const std::string & name ):out_name_ (name){
		callback_q = boost::bind ( & multicast_communication::main_processor::new_quote, this, _1 );
		callback_t = boost::bind ( & multicast_communication::main_processor::new_trade, this, _1 );
	}

	main_processor::main_processor( const quote_call callback_q_, const trade_call callback_t_ ):callback_q ( callback_q_ ),callback_t ( callback_t_ ){
	}

	main_processor::~main_processor(){
	}

	void main_processor::new_trade( const trade_message_ptr & m ){
		boost::mutex::scoped_lock lock( mtx_out_ );
		out_.open ( boost::lexical_cast<std::string>(BINARY_DIR) + "/"  + out_name_ );
		if (!out_.is_open()) 
			throw std::logic_error( "Output file was not opened");
		out_  <<"T "<<m->security_symbol()<<" "<<m->price()<<" "<<m->volume()<<std::endl;
		out_.close();
	}

	void main_processor::new_quote( const quote_message_ptr& m ){
		boost::mutex::scoped_lock lock( mtx_out_ );
		out_.open ( boost::lexical_cast<std::string>(BINARY_DIR) + "/"  + out_name_ );
		if (!out_.is_open()) 
			throw std::logic_error( "Output file was not opened");
		out_<<"Q "<<m->security_symbol()<<" "<<m->bid_price()<<" "<<m->bid_volume()<<" "<<m->offer_price()<<" "<<m->offer_volume()<<std::endl;
		out_.close();
	}
}