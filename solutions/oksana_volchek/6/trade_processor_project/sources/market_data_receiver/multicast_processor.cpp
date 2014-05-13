#include "multicast_processor.h"
#include "consts.h"
#include "market_data_writer.h"
#include <iostream>
#include <fstream>

market_data_receiver::multicast_processor::multicast_processor() :
				trade_thread_size_ (0), quote_thread_size_ (0), 
				trade_ports_ (NULL), quote_ports_ (NULL), trade_queue_ (new tr_queue), quote_queue_ (new qt_queue)
{

}

market_data_receiver::multicast_processor::~multicast_processor() {

}

void market_data_receiver::multicast_processor::start(){
	market_data_receiver::multicast_processor::read_config();
	data_receiver_obj_ = boost::shared_ptr< multicast_communication::data_receiver >(new multicast_communication::data_receiver(trade_thread_size_, 
		quote_thread_size_, trade_ports_, quote_ports_, trade_queue_, quote_queue_));
	minute_calculator_obj_ = boost::shared_ptr< minute_calculator::minute_calculator >(new minute_calculator::minute_calculator(trade_queue_, quote_queue_));
}

void market_data_receiver::multicast_processor::read_config() {
	std::ifstream in;
	in.open(BINARY_DIR + consts::file_path::config_path);
	if (!in.is_open()) {
		std::cout << "Unable to open config file!" << std::endl;
		exit(1);
	}
	size_t trade_ports_amount;
	in >> trade_thread_size_;
	in >> quote_thread_size_;
	in >> trade_ports_amount;

	std::string tmp_address;
	unsigned short tmp_port;
	for (size_t i = 0; i < trade_ports_amount; ++i) {	
		in >> tmp_address;
		in >> tmp_port;
		trade_ports_.push_back(std::make_pair(tmp_address, tmp_port));
	}

	size_t quote_ports_amount;
	in >> quote_ports_amount;
	for (size_t i = 0; i < quote_ports_amount; ++i) {	
		in >> tmp_address;
		in >> tmp_port;
		quote_ports_.push_back(std::make_pair(tmp_address, tmp_port));
	}
	in.close();
}