#include "multicast_communication.h"

multicast_communication::communication::~communication()
{
	communication_threads.join_all();

	interruption();
}

void multicast_communication::communication::process_trade()
{
	std::string msg;
	for(;;)
	{
		if( interrupt )
			return;
		if( trade_queue.pop( msg ) )
			processor->parse( msg, TRADE );  
	}
}

void multicast_communication::communication::process_quote()
{
	std::string msg;
	for(;;)
	{
		if( interrupt )
			return;
		if( quote_queue.pop( msg ) )
			processor->parse( msg, QUOTE );   
	}
}

void multicast_communication::communication::connect( io_service_ptr io_service )
{
	io_service->run();
}

void multicast_communication::communication::interruption()
{
	for( auto it = connections.begin(); it != connections.end(); ++it )
	{
		it->first->stop();
	}
	{
		boost::mutex::scoped_lock lock( interrupt_mtx );
		interrupt = true;
	}

	trade_threads.interrupt_all();
	quote_threads.interrupt_all();
	trade_threads.join_all();
	quote_threads.join_all();
}

void multicast_communication::communication::push_message( std::string& msg, message_type type )
{
	if( type == TRADE )
		trade_queue.push( msg );
	else
		quote_queue.push( msg );
}

void multicast_communication::communication::start()
{
	for( size_t i = 0; i < trade_thread_size; ++i )
		trade_threads.create_thread( boost::bind( &multicast_communication::communication::process_trade, this ) );

	for( size_t i = 0; i < quote_thread_size; ++i )
		quote_threads.create_thread( boost::bind( &multicast_communication::communication::process_quote, this ) );
	
	
	for( auto it = trade_ports.begin(); it != trade_ports.end(); ++it )
	{
		io_service_ptr io_service(  new boost::asio::io_service() );
		udp_listener_ptr listener( new async_udp::udp_listener( *io_service, it->first, it->second, *this, TRADE ) );
		connections.push_back( std::make_pair( io_service, listener ) );
		communication_threads.create_thread( boost::bind( &multicast_communication::communication::connect, this, io_service ) );
	}
	
	for( auto it = quote_ports.begin(); it != quote_ports.end(); ++it )
	{
		io_service_ptr io_service( new boost::asio::io_service() );
		udp_listener_ptr listener( new async_udp::udp_listener( *io_service, it->first, it->second, *this, QUOTE ) );
		connections.push_back( std::make_pair( io_service, listener ) );
		communication_threads.create_thread( boost::bind( &multicast_communication::communication::connect, this, io_service ) );
	}
}
