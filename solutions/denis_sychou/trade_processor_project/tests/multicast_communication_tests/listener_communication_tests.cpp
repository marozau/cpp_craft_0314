#include "test_registrator.h"

#include <udp_listener.h>               

namespace multicast_communication
{
	namespace tests_
	{
		size_t processed()
		{	
			size_t res = 0;
			std::ifstream in;
			in.open( SOURCE_DIR "/tests/data/market_data.dat" , std::ios_base::in );
			
				std::string s;
				while( getline( in, s ) )
				{
					if( s.length() == 0 )
						break;
					++res;
				}

			in.close();

			return res;
		}
	}
}

void multicast_communication::tests_::listener_communication_tests()
{
	{
		boost::asio::io_service io;
		std::vector< address >trade_ports, quote_ports;
		quote_ports.push_back( std::make_pair( "224.0.0.0", 49000 ) );
		trade_ports.push_back( std::make_pair( "224.0.0.1", 49001 ) );

		communication receiver( 2, 2, trade_ports, quote_ports, processor_ptr( new processor( "/tests/data/market_data.dat" ) ) );
		receiver.start();

		std::string qmessage, tmessage;

		std::ifstream input( SOURCE_DIR"/tests/data/quote_tests.txt" );
		std::getline( input, qmessage );
		input.close();

		input.open( SOURCE_DIR"/tests/data/trade_tests.txt" );
		std::getline( input, tmessage );
		input.close();

		boost::asio::ip::udp::endpoint qendpoint( boost::asio::ip::address::from_string( "224.0.0.0" ), 49000 ); 
		boost::asio::ip::udp::socket qsocket( io, qendpoint.protocol() );

		boost::asio::ip::udp::endpoint tendpoint( boost::asio::ip::address::from_string( "224.0.0.1" ), 49001 ); 
		boost::asio::ip::udp::socket tsocket( io, tendpoint.protocol() );
     
		BOOST_CHECK_NO_THROW
			(
				for( size_t i = 0; i < 500; ++i )
				{
					qsocket.send_to( boost::asio::buffer( qmessage ), qendpoint );	
					boost::this_thread::sleep_for( boost::chrono::milliseconds( 5 ) );
				}
				boost::this_thread::sleep_for( boost::chrono::milliseconds( 150 ) );
			);

		BOOST_CHECK_NO_THROW
			(
				for( size_t i = 0; i < 500; ++i )
				{
					tsocket.send_to( boost::asio::buffer( tmessage ), tendpoint );	
					boost::this_thread::sleep_for( boost::chrono::milliseconds( 5 ) );
				}
				boost::this_thread::sleep_for( boost::chrono::milliseconds( 150 ) );
			);

		BOOST_CHECK_NO_THROW
			(
				qmessage = "Wrong_message";
				receiver.processor->parse( qmessage, QUOTE );
			);

		receiver.interruption();
	}

	BOOST_CHECK_EQUAL( processed(), 1000 );
}