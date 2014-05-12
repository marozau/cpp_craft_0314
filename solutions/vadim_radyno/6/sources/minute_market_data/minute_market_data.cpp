#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

#include <signal.h>


#include "minute_market_data.h"
#include "market_data_receiver.h"
#include "market_data_processor.h"
#include "minute_calculator.h"
#include "property.h"

using namespace std;

typedef vector< minute_calculator::minute_datafeed_ptr > vector_min_datafeed_ptr;
typedef map<string, vector_min_datafeed_ptr > map_datafeeds_type;
typedef const vector< pair<string, unsigned short> > const_vector_addr_port;

static void signal_press_ctrl_c(int)
{
	minute_market_data::cond_var_press_ctrl_c.notify_one();
}

template <typename T> static void save(ofstream& out, T const & v)
{
    out.write(reinterpret_cast<const char*>(&v), sizeof( T ) );
}

void save_minute_datafeed( const map_datafeeds_type& data )
{
	for(map_datafeeds_type::const_iterator i = data.begin(); i != data.end(); ++i)
	{
		const string out_file_name = BINARY_DIR "/" + i->first + ".dat";
		ofstream out(out_file_name.c_str(), std::ios_base::binary);
		const vector_min_datafeed_ptr& v = i->second;
		for(vector_min_datafeed_ptr::const_iterator j = v.begin(); j != v.end(); ++j)
		{ 
			minute_calculator::minute_datafeed_ptr p = *j;
			save(out, p->minute_);
			save(out, p->open_price_);
			save(out, p->high_price_);
			save(out, p->low_price_);
			save(out, p->close_price_);
			save(out, p->volume_);
			save(out, p->bid_);
			save(out, p->ask_);
			cout << i->first << " " << *p << endl;
		}
	}
}
void minute_market_data::solution::start()
{
	static const char* config_file = BINARY_DIR "/config.ini";
    	config::reader reader(config_file);
    	if(!reader.opened())
	{ 
		return;
	}
	
	signal(SIGINT, signal_press_ctrl_c);
	cout << "Press [Ctrl] + [C] to stop\n";

	const size_t trade_threads_size = reader.trade_thread_size();
	const size_t quote_threads_size = reader.quote_thread_size();

	const_vector_addr_port& trades = reader.trades();
	const_vector_addr_port& quotes = reader.quotes();

	multicast_communication::market_data_processor processor;
    	multicast_communication::market_data_receiver receiver( trade_threads_size, quote_threads_size, 
								   trades, quotes, processor );

    	receiver.start();

	minute_calculator::calculator calc(processor.trades(), processor.quotes());
    	calc.start();

	boost::mutex mutex_press_ctrl_c; 
    	boost::mutex::scoped_lock lock(mutex_press_ctrl_c);
    	cond_var_press_ctrl_c.wait(lock); 

	receiver.stop();
	calc.stop();
    	map_datafeeds_type data = calc.get_minute_datafeed();

	save_minute_datafeed(data);
}
