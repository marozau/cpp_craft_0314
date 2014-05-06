#ifndef _MARKET_DATA_RECEIVER

#include <vector>

class market_data_receiver
{
	typedef std::pair <std::string, unsigned short> ip_port;
	std::vector <ip_port> trade_ports_;
	std::vector <ip_port> quote_ports_;

	size_t trade_thread_size_;
	size_t quote_thread_size_;
	size_t trade_ports_amount_;
	size_t quote_ports_amount_;

public:
	bool LoadSettings(std::string);
	void Start() const;
};
#define _MARKET_DATA_RECEIVER
#endif //_MARKET_DATA_RECEIVER