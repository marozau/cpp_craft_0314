#include "communication.h" 
#include "separator.h"
#include "udp_listener.h"


#include <string>
#include <vector>

multicast_communication::main_communication::main_communication(	const size_t trade_thread_size,
																	const size_t quote_thread_size,
																	const std::vector< IP_port >& trade_ports,
																	const std::vector< IP_port >& quote_ports,
																	main_processor_ptr processor ): 
																	trade_thread_size_( trade_thread_size ),
																	quote_thread_size_( quote_thread_size ),
																	trade_ports_( trade_ports ),
																	quote_ports_( quote_ports ),
																	processor_( processor ),
																	end_( false ){
}

multicast_communication::main_communication::~main_communication(){

	{
		boost::mutex::scoped_lock lock( end_mtx_ );
		end_ = true;
	}
	link_threads_.join_all();
	trade_threads_.join_all();
	quote_threads_.join_all();

	std::vector<service_ptr>::const_iterator it;

	for (it = run_service_.begin(); it != run_service_.end(); ++it)
		(*it)->stop();
	
}

void multicast_communication::main_communication::read(){

	std::vector<IP_port>::const_iterator it;
	for (it = quote_ports_.begin(); it != quote_ports_.end(); ++it){
		service_ptr io ( new boost::asio::io_service());
		boost::shared_ptr< async_udp::udp_listener > v ( new async_udp::udp_listener (*io, it->first, *this, it->second, QUOTE));
		all_listeners_.push_back(v);
		run_service_.push_back (io);
		link_threads_.create_thread (boost::bind (& multicast_communication::main_communication::new_link, this, io));
	}

	for (it = trade_ports_.begin(); it != trade_ports_.end(); ++it){
		service_ptr io ( new boost::asio::io_service());
		boost::shared_ptr< async_udp::udp_listener > v ( new async_udp::udp_listener (*io, it->first, *this, it->second, TRADE));
		run_service_.push_back (io);
		all_listeners_.push_back(v);
		link_threads_.create_thread (boost::bind (& multicast_communication::main_communication::new_link, this, io));
	}
}

void multicast_communication::main_communication::go(){

	for ( size_t i = 0; i < quote_thread_size_; ++i )
		quote_threads_.create_thread (boost::bind (& multicast_communication::main_communication::pop_quote, this ));

	for ( size_t i = 0; i < trade_thread_size_; ++i )
		trade_threads_.create_thread (boost::bind (& multicast_communication::main_communication::pop_trade, this ));

	main_communication::read();
}

void multicast_communication::main_communication::push_message (const std::string & m, const message_type t){
	if (t == QUOTE)
		queue_q_.push (m);
	else
	if (t == TRADE)
		queue_t_.push (m);
	
}

void multicast_communication::main_communication::pop_trade(){
	std::string str;
	while ( true ){
		{
			boost::mutex::scoped_lock lock( end_mtx_ );
			if ( end_ )
				return ;
		}
		if ( queue_t_.pop (str) )
			const separator_ptr s = separator_ptr ( new separator (str, TRADE, processor_ ));
	}
}

void multicast_communication::main_communication::pop_quote(){	
	std::string str;
	while ( true ){
		{
			boost::mutex::scoped_lock lock ( end_mtx_ );
			if ( end_ )
				return ;
		}
		if ( queue_q_.pop( str ) )
			const separator_ptr s = separator_ptr ( new separator (str, QUOTE, processor_ ));
	}
}

void multicast_communication::main_communication::new_link (service_ptr io){
	io->run();
}
