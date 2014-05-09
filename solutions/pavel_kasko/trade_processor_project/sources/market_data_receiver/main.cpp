#include "market_data_receiver.h"
#include <iostream>
#include <boost\thread.hpp>
#include <csignal>
#include <iostream>

void interrupt_handler(int s);

bool end = false;
int main()
{
	market_data_receiver _market_data_receiver;
	
	std::cout << "Start initializing...\n";
	bool init_res = _market_data_receiver.LoadSettings(BINARY_DIR "/config.ini");
	
	if (init_res)
	{
		std::cout << "Initialized.\n";

		_market_data_receiver.Start();

		std::cout << "Started.\n";

		signal(SIGINT,interrupt_handler);
		
		while(!end)
		{
			//std::cin.get();
			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		}

		_market_data_receiver.Stop();
		std::cout << "Finished.\n";
	}
	else
		std::cout << "Couldn't open config file!\n";
}

void interrupt_handler(int s)
{
	end = true;
}
