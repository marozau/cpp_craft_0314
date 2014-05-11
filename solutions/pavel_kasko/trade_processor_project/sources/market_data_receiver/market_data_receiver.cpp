#include <fstream>
#include <string>
#include "listener.h"
#include "message_types.h"
#include <boost\thread\thread.hpp>
#include <boost\thread\xtime.hpp>
#include "market_data_receiver.h"

market_data_receiver::market_data_receiver() : ag (md){}

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

void market_data_receiver::Start()
{
	using namespace multicast_communication;

	boost::thread_group threads;

	threads.create_thread(boost::bind(&aggregator::StartOutput, &ag));

	for (int i = 0; i < trade_ports_.size(); ++i)
	{	
		listener* lsn_tmp = new listener(trade_ports_[i].first, trade_ports_[i].second, message_type::TRADE);
		(*lsn_tmp).AddHandler(boost::bind(&aggregator::SaveOne, &ag, _1, _2));
		(*lsn_tmp).AddHandler(boost::bind(&minute_calculator::SaveOne, &mc, _1, _2));

		listener_ptr listener_p(lsn_tmp);
		threads.create_thread(boost::bind(&listener::Start, listener_p));
		listeners.push_back(listener_p);
	}

	for (int i = 0; i < quote_ports_.size(); ++i)
	{
		listener* lsn_tmp = new listener(quote_ports_[i].first, quote_ports_[i].second, message_type::QUOTE);
		(*lsn_tmp).AddHandler(boost::bind(&aggregator::SaveOne, &ag, _1, _2));
		(*lsn_tmp).AddHandler(boost::bind(&minute_calculator::SaveOne, &mc, _1, _2));

		listener_ptr listener_p(lsn_tmp);
		threads.create_thread(boost::bind(&listener::Start, listener_p));
		listeners.push_back(listener_p);
	}

	//threads.join_all();
}

void market_data_receiver::Stop()
{
	for (auto i = listeners.begin(); i != listeners.end(); ++i)
	{
		(**i).Stop();
	}

	ag.StopOutput();
}
