#ifndef _MARKET_DATA_RECEIVER

#include <vector>
#include <list>
#include <listener.h>
#include <boost\shared_ptr.hpp>
#include "aggregator.h"
#include "minute_calculator.h"

typedef std::pair <std::string, unsigned short> ip_port;
class market_data_receiver
{	
	std::vector <ip_port> trade_ports_;
	std::vector <ip_port> quote_ports_;

	size_t trade_thread_size_;
	size_t quote_thread_size_;
	size_t trade_ports_amount_;
	size_t quote_ports_amount_;
	typedef boost::shared_ptr<multicast_communication::listener> listener_ptr;
	
	std::vector<listener_ptr> listeners;
	multicast_communication::market_data_processor_derived md;
	multicast_communication::aggregator ag;
	multicast_communication::minute_calculator mc;

public:
	market_data_receiver();
	bool LoadSettings(std::string);
	void Start();
	void Stop();
};
#define _MARKET_DATA_RECEIVER
#endif //_MARKET_DATA_RECEIVER