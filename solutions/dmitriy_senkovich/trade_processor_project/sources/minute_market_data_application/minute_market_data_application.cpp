#include "minute_market_data.h"
#include "market_data_processor.h"
#include "minute_calculator.h"
#include "multicast_communication.h"
#include "quote_message.h"
#include "trade_message.h"
#include "udp_listener.h"
#include <fstream>
#include <signal.h>

void stop( int fict_param = 0 )
{
	trade_processor_project::minute_market_data::stop();
	exit( 0 );
}

int main()
{
	signal( SIGINT, stop );
	size_t trade_thread_size;
	size_t quote_thread_size;
	size_t trade_ports_amount;
	size_t quote_ports_amount;
	std::vector< std::pair< std::string, unsigned short > > trade_ports;
	std::vector< std::pair< std::string, unsigned short > > quote_ports;
	std::ifstream input( SOURCE_DIR"/configs.ini" );
	if( !input.is_open() )
	{
		std::cout << "Input file isn't opened\n";
		return 1;
	}
	std::string buff;
	if( !getline( input, buff ) )
	{
		std::cout << "Error while reading input data\n";
		return 1;
	}
	sscanf( buff.c_str(), "%Iu", &trade_thread_size );
	if( !getline( input, buff ) )
	{
		std::cout << "Error while reading input data\n";
		return 1;
	}
	sscanf( buff.c_str(), "%Iu", &quote_thread_size );
	if( !getline( input, buff ) )
	{
		std::cout << "Error while reading input data\n";
		return 1;
	}
	sscanf( buff.c_str(), "%Iu", &trade_ports_amount );
	for( size_t i = 0; i < trade_ports_amount; i++ )
	{
		if( !getline( input, buff ) )
		{
			std::cout << "Error while reading input data\n";
			return 1;
		}
		std::string buff_ip;
		size_t j = 0;
		while( buff[j] != ' ' )
		{
			buff_ip.push_back( buff[j] );
			j++;
		}
		unsigned short buff_port;
		buff.erase( buff.begin(), buff.begin() + j + 1 );
		sscanf( buff.c_str(), "%d", &buff_port );
		trade_ports.push_back( std::make_pair( buff_ip, buff_port ) );
	}
	if( !getline( input, buff ) )
	{
		std::cout << "Error while reading input data\n";
		return 1;
	}
	sscanf( buff.c_str(), "%Iu", &quote_ports_amount );
	for( size_t i = 0; i < quote_ports_amount; i++ )
	{
		if( !getline( input, buff ) )
		{
			std::cout << "Error while reading input data\n";
			return 1;
		}
		std::string buff_ip;
		size_t j = 0;
		while( buff[j] != ' ' )
		{
			buff_ip.push_back( buff[j] );
			j++;
		}
		unsigned short buff_port;
		buff.erase( buff.begin(), buff.begin() + j + 1 );
		sscanf( buff.c_str(), "%d", &buff_port );
		quote_ports.push_back( std::make_pair( buff_ip, buff_port ) );
	}
	input.close();
	std::queue<trade_processor_project::market_data_processor::union_message> union_message_queue;
	std::queue<trade_processor_project::market_data_processor::datafeed> datafeed_queue;
	trade_processor_project::market_data_processor processor( union_message_queue, datafeed_queue );
	trade_processor_project::minute_market_data application( trade_ports_amount, quote_ports_amount, trade_thread_size, quote_thread_size, trade_ports, quote_ports, processor );
	application.start();
	return 0;
}