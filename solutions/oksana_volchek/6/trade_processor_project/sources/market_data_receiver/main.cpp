#include <stdexcept>
#include <iostream>
#include <csignal>
#include "multicast_processor.h"

namespace for_stop {
	boost::mutex wait_ctrl_c;
	boost::condition_variable cond;
}

void ctrl_c_handler(int)
{
	boost::mutex::scoped_lock lock(for_stop::wait_ctrl_c);
	for_stop::cond.notify_one();
}

int main() {
	try {
		market_data_receiver::multicast_processor mult_proc = market_data_receiver::multicast_processor();
		mult_proc.start();

		boost::mutex::scoped_lock lock(for_stop::wait_ctrl_c);
		signal(SIGINT, ctrl_c_handler);
		for_stop::cond.wait(lock);
	}
	catch(...) {
		std::cerr << "Error!" << std::endl;
	}
}