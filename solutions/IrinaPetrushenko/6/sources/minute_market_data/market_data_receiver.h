#ifndef _MARKET_DATA_RECEIVER_H_
#define _MARKET_DATA_RECEIVER_H_

#include <iostream>
#include <fstream>
#include <vector>

#include <communication.h>
#include <main_processor.h>
#include <minute_calculator.h>

using namespace std;

class  market_data_receiver{
		private:
			boost::mutex mtx_print_;

			typedef std::pair <std::string, unsigned short> IP_port;
			vector <IP_port> trade_ports_;
			vector <IP_port> quote_ports_;

			size_t trade_thread_size_;
			size_t quote_thread_size_;
			size_t trade_ports_amount_;
			size_t quote_ports_amount_;

			typedef boost::shared_ptr< minute_calculator::calculator > calculator_ptr;
			typedef boost::shared_ptr< multicast_communication::main_communication > main_communication_ptr;
			static void for_signal_(int);

		public:
			explicit market_data_receiver();
			~market_data_receiver();
			void go();
			void print(const minute_calculator::minute_datafeed_ptr& data);
}; 


#endif //_MARKET_DATA_RECEIVER_H_