#include "test_registrator.h"

#include "multicast_communication.h"
#include "market_data_processor.h"
#include "quote_message.h"
#include "trade_message.h"
#include "udp_listener.h"
#include <fstream>
#include <map>

using namespace trade_processor_project;

typedef boost::shared_ptr< std::string > buffer_type;
typedef std::map< std::string, size_t > data_map;

void service_thread( boost::asio::io_service& service )
{	
	service.run();
}

void tests_::multicast_communication_tests()
{
	{
		std::queue<market_data_processor::union_message> um_queue;
		std::queue<market_data_processor::datafeed> d_queue;
		market_data_processor processor( um_queue, d_queue );
		std::vector< std::pair< std::string, unsigned short > > trade_ports, quote_ports;
		quote_ports.push_back( std::make_pair( "224.0.0.0", 50000 ));
		trade_ports.push_back( std::make_pair( "224.0.0.1", 50001 ));
		multicast_communication udp_controller( 1, 1, 4, 4, trade_ports, quote_ports, processor );
		boost::thread udp_controller_thread( boost::bind( &multicast_communication::start, &udp_controller ) );

		boost::asio::io_service service;
		boost::asio::ip::udp::endpoint quote_endpoint( boost::asio::ip::address::from_string( "224.0.0.0" ), 50000 ); 
		boost::asio::ip::udp::socket quote_socket( service, quote_endpoint.protocol() );
		boost::asio::ip::udp::endpoint trade_endpoint( boost::asio::ip::address::from_string( "224.0.0.1" ), 50001 ); 
		boost::asio::ip::udp::socket trade_socket( service, trade_endpoint.protocol() );
		boost::thread receive_messages( boost::bind( service_thread, boost::ref( service ) ) );

		std::ifstream quote_input( SOURCE_DIR"/tests/data/quote_data.dat" );
		std::ifstream trade_input( SOURCE_DIR"/tests/data/trade_data.dat" );
		std::string buffer;
		for( size_t i = 0; i < 1000; i++ )
		{
			if( i%2 )
			{
				getline( quote_input, buffer );
				quote_socket.send_to( boost::asio::buffer( buffer ), quote_endpoint );
				boost::this_thread::sleep_for( boost::chrono::milliseconds( 5 ) );
			}
			else
			{
				getline( trade_input, buffer );
				trade_socket.send_to( boost::asio::buffer( buffer ), trade_endpoint );
				boost::this_thread::sleep_for( boost::chrono::milliseconds( 5 ) );
			}
		}
		boost::this_thread::sleep_for( boost::chrono::seconds( 1 ) );
		quote_input.close();
		trade_input.close();
		multicast_communication::stop();
		udp_controller_thread.join();

		std::ifstream data( SOURCE_DIR"/multicast_communication_output/market_data.dat" );
		std::ifstream data_to_compare( SOURCE_DIR"/tests/data/market_data_to_compare.dat" );
		size_t data_lines_amount = 0;
		size_t data_to_compare_lines_amount = 0;
		data_map data_lines;
		data_map data_to_compare_lines;
		while( getline( data, buffer ) )
		{
			data_lines[buffer]++;
			data_lines_amount++;
		}
		while( getline( data_to_compare, buffer ) )
		{
			data_to_compare_lines[buffer]++;
			data_to_compare_lines_amount++;
		}
		data.close();
		data_to_compare.close();

		BOOST_CHECK_EQUAL( data_lines_amount, data_to_compare_lines_amount );
		
		data_map::iterator data_to_compare_iter = data_lines.begin();
		for( data_map::iterator data_iter = data_lines.begin(); data_iter != data_lines.end(); data_iter++ )
		{
			BOOST_CHECK_EQUAL( data_iter->second, data_to_compare_iter->second );
			data_to_compare_iter++;
		}

		std::remove( SOURCE_DIR"/multicast_communication_output/market_data.dat" );
	}
}
