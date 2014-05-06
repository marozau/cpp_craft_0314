#include "market_data_receiver.h"
#include <iostream>
int main()
{
	market_data_receiver _market_data_receiver;
	
	std::cout << "Start initializing\n";
	bool init_res = _market_data_receiver.LoadSettings(BINARY_DIR "/config.ini");
	
	if (init_res)
	{
		std::cout << "Initialized\n";

		_market_data_receiver.Start();
	}
	std::cout << "Couldn't open config file!\n";
}
