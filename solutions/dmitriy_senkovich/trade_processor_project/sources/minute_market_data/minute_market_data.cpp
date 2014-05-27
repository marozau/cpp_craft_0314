#include "minute_market_data.h"

using namespace trade_processor_project;

boost::thread minute_market_data::start_thread_;
bool minute_market_data::to_stop = false;
boost::mutex minute_market_data::lock_to_stop;

minute_market_data::minute_market_data( const size_t trade_ports_amount, const size_t quote_ports_amount, const size_t trade_thread_size, const size_t quote_thread_size, const std::vector< address >& trade_ports, const std::vector< address >&  quote_ports, market_data_processor& processor )
	:trade_ports_amount_( trade_ports_amount )
	,quote_ports_amount_( quote_ports_amount )
	,trade_thread_size_( trade_thread_size )
	,quote_thread_size_( quote_thread_size )
	,trade_ports_( trade_ports )
	,quote_ports_( quote_ports )
	,processor_( processor )
{
}
void minute_market_data::start()
{
	multicast_communication udp_controller( trade_ports_amount_, quote_ports_amount_, trade_thread_size_, quote_thread_size_, trade_ports_, quote_ports_, processor_ );
	minute_calculator calculator( processor_ );
	boost::thread udp_controller_thread( boost::bind( &multicast_communication::start, &udp_controller ) );
	boost::thread calculator_thread( boost::bind( &minute_calculator::start, &calculator ) );
	start_thread_ = boost::thread( boost::bind( &minute_market_data::create_data, this ) );
	start_thread_.join();
}
void minute_market_data::create_data()
{
	while( true )
	{
		market_data_processor::datafeed data;
		{
			boost::unique_lock< boost::mutex > lock( market_data_processor::lock_datafeed_queue_access );
			while( processor_.datafeed_queue.empty() )
			{
				{
					boost::mutex::scoped_lock lock( minute_market_data::lock_to_stop );
					if( minute_market_data::to_stop )
						return;
				}
				market_data_processor::datafeed_queue_cond_var.wait( lock );
			}
			{
				boost::mutex::scoped_lock lock( minute_market_data::lock_to_stop );
				if( minute_market_data::to_stop )
				{
					if( processor_.datafeed_queue.empty() )
						return;
					stop_work();
					return;
				}
			}
			data = processor_.datafeed_queue.front();
			processor_.datafeed_queue.pop();
			lock.unlock();
		}
		write_datafeed( data );
	}
}
void minute_market_data::write_datafeed( market_data_processor::datafeed& data )
{
	std::string output_name = SOURCE_DIR"/minute_market_data_output/";
	output_name += data.stock_name;
	output_name += ".dat";
	files_to_delete.insert( data.stock_name );
	std::ofstream output( output_name.c_str(), std::ios_base::binary|std::ios_base::app );
	if( !output.is_open() )
		return;
	if( !output.write( reinterpret_cast< char* >( &data.seconds ), sizeof( boost::uint32_t ) ) )
		return;
	if( !output.write( data.stock_name, 16 ) )
		return;
	if( !output.write( reinterpret_cast< char* >( &data.open_price ), sizeof( double ) ) )
		return;
	if( !output.write( reinterpret_cast< char* >( &data.high_price ), sizeof( double ) ) )
		return;
	if( !output.write( reinterpret_cast< char* >( &data.low_price ), sizeof( double ) ) )
		return;
	if( !output.write( reinterpret_cast< char* >( &data.close_price ), sizeof( double ) ) )
		return;
	if( !output.write( reinterpret_cast< char* >( &data.volume ), sizeof( double ) ) )
		return;
	if( !output.write( reinterpret_cast< char* >( &data.bid ), sizeof( double ) ) )
		return;
	if( !output.write( reinterpret_cast< char* >( &data.ask ), sizeof( double ) ) )
		return;
	output.close();
}
void minute_market_data::stop_work()
{
	while( !processor_.datafeed_queue.empty() )
	{
		market_data_processor::datafeed data;
		data = processor_.datafeed_queue.front();
		processor_.datafeed_queue.pop();
		write_datafeed( data );
	}
}
void minute_market_data::stop()
{
	multicast_communication::stop();
	minute_calculator::stop();
	{
		boost::mutex::scoped_lock lock( minute_market_data::lock_to_stop );
		minute_market_data::to_stop = true;
	}
	market_data_processor::datafeed_queue_cond_var.notify_one();
	start_thread_.join();
}