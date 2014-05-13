#include "test_registrator.h"

#include "minute_market_data.h"
#include "minute_calculator.h"
#include "multicast_communication.h"
#include <fstream>

using namespace trade_processor_project;

typedef boost::shared_ptr< trade_message > tr_msg_ptr;
typedef boost::shared_ptr< quote_message > qu_msg_ptr;
typedef boost::shared_ptr< std::string > buffer_type;
typedef std::map< std::string, size_t > data_map;
typedef std::set< std::string > filename_set;

void service_thread( boost::asio::io_service& service )
{	
	service.run();
}

void tests_::minute_market_data_tests()
{
	{
		std::queue<market_data_processor::union_message> um_queue;
		std::queue<market_data_processor::datafeed> d_queue;
		market_data_processor processor( um_queue, d_queue );
		std::vector< std::pair< std::string, unsigned short > > trade_ports, quote_ports;
		quote_ports.push_back( std::make_pair( "224.0.0.0", 50000 ));
		trade_ports.push_back( std::make_pair( "224.0.0.1", 50001 ));
		minute_market_data application( 1, 1, 4, 4, trade_ports, quote_ports, processor );
		boost::thread application_thread( boost::bind( &minute_market_data::start, &application ) );

		boost::asio::io_service service;
		boost::asio::ip::udp::endpoint quote_endpoint( boost::asio::ip::address::from_string( "224.0.0.0" ), 50000 ); 
		boost::asio::ip::udp::socket quote_socket( service, quote_endpoint.protocol() );
		boost::asio::ip::udp::endpoint trade_endpoint( boost::asio::ip::address::from_string( "224.0.0.1" ), 50001 ); 
		boost::asio::ip::udp::socket trade_socket( service, trade_endpoint.protocol() );
		boost::thread receive_messages( boost::bind( service_thread, boost::ref( service ) ) );

		std::ifstream quote_input( SOURCE_DIR"/tests/data/quote_data.dat" );
		std::ifstream trade_input( SOURCE_DIR"/tests/data/trade_data.dat" );
		std::string buffer;
		for( size_t i = 0; i < 2000; i++ )
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
		boost::this_thread::sleep_for( boost::chrono::seconds( 2 ) );
		quote_input.close();
		trade_input.close();
		service.stop();
		receive_messages.join();
		minute_market_data::stop();
		application_thread.join();

		for( filename_set::iterator files_to_delete_iter = application.files_to_delete.begin(); files_to_delete_iter != application.files_to_delete.end(); files_to_delete_iter++ )
		{
			std::string curr_datafeed_name = SOURCE_DIR"/minute_market_data_output/" + *files_to_delete_iter + ".dat";
			std::string curr_datafeed_name_to_compare = SOURCE_DIR"/tests/data/datafeed_to_compare/" + *files_to_delete_iter + ".dat";
			std::ifstream curr_datafeed( curr_datafeed_name.c_str() );
			std::ifstream curr_datafeed_to_compare( curr_datafeed_name_to_compare.c_str() );
			std::string buffer;
			std::string buffer_to_compare;
			while( getline( curr_datafeed, buffer ) )
			{
				getline( curr_datafeed_to_compare, buffer_to_compare );
				BOOST_CHECK_EQUAL( strcmp( buffer.c_str(), buffer_to_compare.c_str() ), 0 );
			}
			curr_datafeed_to_compare.get();
			BOOST_CHECK_EQUAL( curr_datafeed_to_compare.eof(), true );
			curr_datafeed.close();
			curr_datafeed_to_compare.close();
			std::remove( curr_datafeed_name.c_str() );
		}
	}
}
