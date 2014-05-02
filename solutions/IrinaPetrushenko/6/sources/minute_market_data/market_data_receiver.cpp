#include "market_data_receiver.h"
#include "main_processor.h"
#include "communication.h"

#include <boost\lexical_cast.hpp>

#include <stdlib.h> 

market_data_receiver::market_data_receiver(){
}

market_data_receiver::~market_data_receiver(){
}

void market_data_receiver::for_signal_( int p ){
	exit( EXIT_SUCCESS);
}

void market_data_receiver::go(){
	signal( SIGINT, for_signal_ );
	ifstream in_;
	in_.open(BINARY_DIR"/config.ini");
	if (!in_.is_open())
			throw logic_error( "Config file was not opened");
	in_>>trade_thread_size_>>quote_thread_size_;

	in_>>trade_ports_amount_;

	string ip;
	unsigned short port; 
	for (size_t i = 0; i < trade_ports_amount_; ++i){
		in_>>ip>>port;
		trade_ports_.push_back(make_pair(ip, port));
	}

	in_>>quote_ports_amount_;

	for (size_t i = 0; i < quote_ports_amount_; ++i){
		in_>>ip>>port;
		quote_ports_.push_back(make_pair(ip, port));
	}
	const calculator_ptr cc = calculator_ptr (new minute_calculator::calculator (boost::bind (&market_data_receiver::print, this, _1)));
	const main_communication_ptr c = main_communication_ptr (new multicast_communication::main_communication (trade_thread_size_, 
																										quote_thread_size_, 
																										trade_ports_, 
																										quote_ports_, 
																										multicast_communication::main_processor_ptr (new multicast_communication::main_processor (	boost::bind (&minute_calculator::calculator::new_quote,*cc, _1 ),
																																																	boost::bind (&minute_calculator::calculator::new_trade,*cc, _1 ) ))));
	c->go();
	in_.close();
}

void market_data_receiver::print (const minute_calculator::minute_datafeed_ptr & m){
		boost::mutex::scoped_lock lock (mtx_print_);
		ofstream out;
		const string name = boost::lexical_cast<std::string> ("/") + boost::lexical_cast<std::string> (m->stock_name)+ ".dat";
		out.open (boost::lexical_cast<std::string>(BINARY_DIR) + name , ios::binary );
		out.write (reinterpret_cast <char*> (&(*m)), sizeof (*m));
		out.close ();
}