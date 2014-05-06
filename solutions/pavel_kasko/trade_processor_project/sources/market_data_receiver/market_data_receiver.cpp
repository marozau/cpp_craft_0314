#include "market_data_receiver.h"
#include <fstream>
#include <string>
#include "listener.h"
#include "market_data_processor.h"

bool market_data_receiver::LoadSettings(std::string config_file_path)
{
	std::ifstream input_file(config_file_path);

	if (!input_file.good())
		return false;

	input_file >> trade_thread_size_ >> quote_thread_size_ >> trade_ports_amount_;

	for (auto i = 0; i < trade_ports_amount_; ++i)
	{
		std::string ip;
		unsigned short port;
		input_file >> ip >> port;
		trade_ports_.push_back(std::make_pair(ip, port));
	}

	input_file >> quote_ports_amount_;
	for (auto i = 0; i < quote_ports_amount_; ++i)
	{
		std::string ip;
		unsigned short port;
		input_file >> ip >> port;
	 	quote_ports_.push_back(std::make_pair(ip, port));
	}

	input_file.close();
	return true;
}

void market_data_receiver::Start() const
{
	listener
}