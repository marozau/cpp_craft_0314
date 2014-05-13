#include "multicast_communication.h"
#include "minute_calculator.h"
#include <signal.h>
#include <fstream>

class Solution
{
	size_t trade_thread_size
		   , quote_thread_size 
		   , trade_ports_amount
		   , quote_ports_amount;

	std::vector< multicast_communication::address > trade_ports, quote_ports;

	static void button_handler( int )
	{
		exit( 0 );
	}

	std::ofstream out;
	boost::mutex output_mtx;

	void print( const minute_calculator::minute_datafeed_ptr& datafeed )
	{
		boost::mutex::scoped_lock lock( output_mtx );
		out.open( SOURCE_DIR + std::string( datafeed->stock_name ) + std::string( ".dat" ), std::ios_base::binary | std::ios_base::app ); 
		out.write( reinterpret_cast< char* >( &( *datafeed ) ), sizeof( *datafeed ) ); 
		out.close();
	}
public:
	Solution() {}

	void process()
	{
		std::ifstream config( SOURCE_DIR "/config.ini" );
		if( !config.is_open() )
			throw std::exception( "Can't open config.ini" );

		signal( SIGINT, button_handler );

		config >> trade_thread_size >> quote_thread_size >> trade_ports_amount;

		std::string ip;
		unsigned short port;

		for( size_t i = 0; i < trade_ports_amount; i++ )
		{
			config >> ip >> port;
			trade_ports.push_back( std::make_pair( ip, port ) );
		}

		config >> quote_ports_amount;

		for( size_t i = 0; i < quote_ports_amount; i++ )
		{
			config >> ip >> port;
			quote_ports.push_back( std::make_pair( ip, port ) );
		}

		config.close();

		minute_calculator::minute_calculator_ptr calculator( new minute_calculator::minute_calculator( boost::bind( &Solution::print, this, _1 ) ) );

		multicast_communication::processor_ptr processor( new multicast_communication::processor( boost::bind( &minute_calculator::minute_calculator::new_trade, *calculator, _1 )
																								, boost::bind( &minute_calculator::minute_calculator::new_quote, *calculator, _1 ) ) );

		multicast_communication::communication_ptr communicator( new multicast_communication::communication( trade_thread_size, quote_thread_size, trade_ports, quote_ports, processor ) );

		communicator->start();
	}
};

int main()
{
	Solution s;
	s.process();

	return 1;
}
