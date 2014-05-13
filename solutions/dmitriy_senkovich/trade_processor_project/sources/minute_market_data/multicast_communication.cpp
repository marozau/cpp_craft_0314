#include "multicast_communication.h"
#include <boost/lexical_cast.hpp>

using namespace trade_processor_project;

typedef boost::shared_ptr< std::string > buffer_type;
typedef boost::shared_ptr< boost::asio::io_service > io_service_ptr;

bool multicast_communication::to_stop = false;
boost::mutex multicast_communication::lock_to_stop;
boost::thread_group multicast_communication::listening_threads_;
boost::thread_group multicast_communication::parsing_threads_;
std::vector< std::pair< io_service_ptr, udp_listener_ptr > > multicast_communication::listeners_storage_;
std::ofstream multicast_communication::output_( SOURCE_DIR"/multicast_communication_output/market_data.dat" );

multicast_communication::multicast_communication( const size_t trade_ports_amount, const size_t quote_ports_amount, const size_t trade_thread_size, const size_t quote_thread_size, const std::vector< address >& trade_ports, const std::vector< address >& quote_ports, market_data_processor& processor )
	:SOH( 0x01 )
	,ETX( 0x03 )
	,US( 0x1F )
	,trade_ports_amount_( trade_ports_amount )
	,quote_ports_amount_( quote_ports_amount )
	,trade_thread_size_( trade_thread_size )
	,quote_thread_size_( quote_thread_size )
	,trade_ports_( trade_ports )
	,quote_ports_( quote_ports )
	,processor_( processor )
{
}
void multicast_communication::stop()
{
	{
		boost::mutex::scoped_lock lock( udp_listener::lock_to_stop );
		udp_listener::to_stop = true;
	}
	for( int i = 0; i < listeners_storage_.size(); i++ )
		listeners_storage_[i].first->stop();
	listening_threads_.join_all();
	{
		boost::mutex::scoped_lock lock( multicast_communication::lock_to_stop );
		multicast_communication::to_stop = true;
	}
	{
		boost::mutex::scoped_lock lock( udp_listener::lock_quote_queue_ );
		udp_listener::quote_cond_var_.notify_all();
	}
	{
		boost::mutex::scoped_lock lock( udp_listener::lock_trade_queue_ );
		udp_listener::trade_cond_var_.notify_all();
	}
	multicast_communication::parsing_threads_.join_all();
	output_.close();
}
void multicast_communication::run_io_service( const io_service_ptr& service )
{
	service->run();
}
void multicast_communication::start()
{
	for( size_t i = 0; i < trade_ports_amount_; i++ )
	{
		io_service_ptr service( new boost::asio::io_service() );
		listeners_storage_.push_back( std::make_pair( service, udp_listener_ptr( new udp_listener( *service, trade_ports_[i].first, trade_ports_[i].second, true, trade_block_queue ) ) ) );
		listening_threads_.create_thread( boost::bind( &multicast_communication::run_io_service, this, service ) );
	}
	for( size_t i = 0; i < quote_ports_amount_; i++ )
	{
		io_service_ptr service( new boost::asio::io_service() );
		listeners_storage_.push_back( std::make_pair( service, udp_listener_ptr( new udp_listener( *service, quote_ports_[i].first, quote_ports_[i].second, false, quote_block_queue ) ) ) );
		listening_threads_.create_thread( boost::bind( &multicast_communication::run_io_service, this, service ) );
	}

	for( size_t i = 0; i < trade_thread_size_; i++ )
		parsing_threads_.create_thread( boost::bind( &multicast_communication::make_new_message, this, true ) );
	for( size_t i = 0; i < quote_thread_size_; i++ )
		parsing_threads_.create_thread( boost::bind( &multicast_communication::make_new_message, this, false ) );
}
void multicast_communication::move_pos( std::stringstream& str_stream, const size_t move )
{
	std::streamoff pos = str_stream.tellg();
	str_stream.seekg( pos + move );
}
void multicast_communication::read_double( double& dest, std::stringstream& str_stream, const size_t amount )
{
	char* buff_str = new char[amount+1];
	str_stream.read( buff_str, amount );
	std::string buff;
	size_t i = 0;
	for( i = 0; ( i < amount ) && ( isdigit( buff_str[i] ) ) ; i++ )
		buff += buff_str[i];
	delete []buff_str;
	dest = boost::lexical_cast<double> ( buff );
	move_pos( str_stream, amount - i );
}
void multicast_communication::read_string( std::string& dest, std::stringstream& str_stream, const size_t amount )
{
	char* buff_str =  new char[amount+1];
	str_stream.read( buff_str, amount );
	size_t i = 0;
	for( i = 0; ( i < amount ); i++ )
		dest += buff_str[i];
	delete []buff_str;
	move_pos( str_stream, amount - i );
}
void multicast_communication::make_new_message( const bool trade )
{
	while( true )
	{
		buffer_type bt;
		if( trade )
		{
			boost::unique_lock< boost::mutex > lock( udp_listener::lock_trade_queue_ );
			while( trade_block_queue.empty() )
			{
				{
					boost::mutex::scoped_lock lock( multicast_communication::lock_to_stop );
					if( to_stop )
						return;
				}
				udp_listener::trade_cond_var_.wait( lock );
			}
			bt = trade_block_queue.front();
			trade_block_queue.pop();
			lock.unlock();
		}
		else
		{
			boost::unique_lock< boost::mutex > lock( udp_listener::lock_quote_queue_ );
			while( quote_block_queue.empty() )	
			{
				{
					boost::mutex::scoped_lock lock( multicast_communication::lock_to_stop );
					if( to_stop )
						return;
				}
				udp_listener::quote_cond_var_.wait( lock );
			}
			bt = quote_block_queue.front();
			quote_block_queue.pop();
			lock.unlock();
		}
		std::stringstream buff_stream( *bt );
		if( ( static_cast<char>( buff_stream.get() ) ) != SOH )
			continue;
		try
		{
			if( trade )
			{
				std::vector< trade_message > buff_msg_vector;
				while( true )
				{ 
					char curr_category = static_cast<char>( buff_stream.get() );
					char curr_type = static_cast<char>( buff_stream.get() );
					if( ( ( curr_category == 'E' ) || ( curr_category == 'L' ) ) && ( curr_type == 'I' )  )
					{
						trade_message buff_msg;
						move_pos( buff_stream, 16 );
						char hours = static_cast<char>( buff_stream.get() );
						char minutes = static_cast<char>( buff_stream.get() );
						buff_msg.set_minute() = ( static_cast<boost::uint32_t>( hours ) - 48 ) * 60 + ( static_cast<boost::uint32_t>( minutes ) - 48 );
						move_pos( buff_stream, 4 );
						read_string( buff_msg.set_security_symbol(), buff_stream, 3 );
						move_pos( buff_stream, 1 );
						read_double( buff_msg.set_trade_volume(), buff_stream, 4 );
						read_string( buff_msg.set_price_denominator_indicator(), buff_stream, 1 );
						read_double( buff_msg.set_trade_price(), buff_stream, 8 );
						move_pos( buff_stream, 3 );
						char end = buff_stream.get();
						if( ( end != US ) && ( end != ETX ) )
							throw std::exception();
						if( end == ETX )
						{
							buff_msg_vector.push_back( buff_msg );
							break;
						}
						buff_msg_vector.push_back( buff_msg );
						continue;
					}
					if( ( ( curr_category == 'B' ) || ( curr_category == 'E' ) || ( curr_category == 'L' ) ) && ( curr_type == 'B' ) )
					{
						trade_message buff_msg;
						move_pos( buff_stream, 16 );
						char hours = static_cast<char>( buff_stream.get() );
						char minutes = static_cast<char>( buff_stream.get() );
						buff_msg.set_minute() = ( static_cast<boost::uint32_t>( hours ) - 48 ) * 60 + ( static_cast<boost::uint32_t>( minutes ) - 48 );
						move_pos( buff_stream, 4 );
						read_string( buff_msg.set_security_symbol(), buff_stream, 11 );
						move_pos( buff_stream, 21 );
						read_string( buff_msg.set_price_denominator_indicator(), buff_stream, 1 );
						read_double( buff_msg.set_trade_price(), buff_stream, 12 );
						read_double( buff_msg.set_trade_volume(), buff_stream, 9 );
						move_pos( buff_stream, 4 );
						char end = buff_stream.get();
						if( ( end != US ) && ( end != ETX ) )
							throw std::exception();
						if( end == ETX )
						{
							buff_msg_vector.push_back( buff_msg );
							break;
						}
						buff_msg_vector.push_back( buff_msg );
						continue;
					}
					throw std::exception();
				}
				size_t length = buff_msg_vector.size();
				for( size_t i = 0; i < length; i++ )
				{
					{
						boost::mutex::scoped_lock lock( lock_output_ );
						output_ << "T " << std::fixed;
						size_t j = 0;
						size_t curr_size = buff_msg_vector[i].security_symbol().size();
						while( ( j != curr_size ) && ( buff_msg_vector[i].security_symbol()[j] != (char)32 ) )
						{
							output_ << buff_msg_vector[i].security_symbol()[j];
							j++;
						}
						output_ << " " << std::setprecision( 2 ) << buff_msg_vector[i].price() << " " << std::setprecision( 1 ) << buff_msg_vector[i].volume() << "\n";
					}
					trade_message_ptr tr_msg( new trade_message( buff_msg_vector[i] ) );
					quote_message_ptr qu_msg( new quote_message() );
					market_data_processor::union_message u_m( true, tr_msg, qu_msg );
					{
						boost::unique_lock< boost::mutex > lock( market_data_processor::lock_union_message_queue_access );
						processor_.union_message_queue.push( u_m );
						market_data_processor::union_message_queue_cond_var.notify_one();
						lock.unlock();
					}
				}
			}
			else
			{
				std::vector< quote_message > buff_msg_vector;
				while( true )
				{ 
					char curr_category = static_cast<char>( buff_stream.get() );
					char curr_type = static_cast<char>( buff_stream.get() );
					if( ( ( curr_category == 'E' ) || ( curr_category == 'L' ) ) && ( curr_type == 'D' )  )
					{
						quote_message buff_msg;
						move_pos( buff_stream, 16 );
						char hours = static_cast<char>( buff_stream.get() );
						char minutes = static_cast<char>( buff_stream.get() );
						buff_msg.set_minute() = ( static_cast<boost::uint32_t>( hours ) - 48 ) * 60 + ( static_cast<boost::uint32_t>( minutes ) - 48 );
						move_pos( buff_stream, 4 );
						read_string( buff_msg.set_security_symbol(), buff_stream, 3 );
						move_pos( buff_stream, 3 );
						read_string( buff_msg.set_bid_price_denominator_indicator(), buff_stream, 1 );
						read_double( buff_msg.set_bid_price(), buff_stream, 8 );
						read_double( buff_msg.set_bid_size_of_units_of_trade(), buff_stream, 3 );
						move_pos( buff_stream, 1 );
						read_string( buff_msg.set_offer_price_denominator_indicator(), buff_stream, 1 );
						read_double( buff_msg.set_offer_price(), buff_stream, 8 );
						read_double( buff_msg.set_offer_size_of_units_of_trade(), buff_stream, 3 );
						move_pos( buff_stream, 3 );
						char end = buff_stream.get();
						if( ( end != US ) && ( end != ETX ) )
							throw std::exception();
						if( end == ETX )
						{
							buff_msg_vector.push_back( buff_msg );
							break;
						}
						buff_msg_vector.push_back( buff_msg );
						continue;
					}
					if( ( ( curr_category == 'B' ) || ( curr_category == 'E' ) || ( curr_category == 'L' ) ) && ( curr_type == 'B' ) )
					{
						quote_message buff_msg;
						buff_msg.if_long = true;
						move_pos( buff_stream, 16 );
						char hours = static_cast<char>( buff_stream.get() );
						char minutes = static_cast<char>( buff_stream.get() );
						buff_msg.set_minute() = ( static_cast< boost::uint32_t >( hours ) - 48 ) * 60 + ( static_cast< boost::uint32_t >( minutes ) - 48 );
						move_pos( buff_stream, 4 );
						read_string( buff_msg.set_security_symbol(),buff_stream, 11 );
						move_pos( buff_stream, 16 );
						read_string( buff_msg.set_lower_limit_price_band_denominator_indicator(), buff_stream, 1 );
						read_double( buff_msg.set_lower_limit_price_band(), buff_stream, 12 );
						read_double( buff_msg.set_bid_size_in_units_of_trade(), buff_stream, 7 );
						read_string( buff_msg.set_upper_limit_price_band_denominator_indicator(), buff_stream, 1 );
						read_double( buff_msg.set_upper_limit_price_band(), buff_stream, 12 );
						read_double( buff_msg.set_offer_size_in_units_of_trade(), buff_stream, 7 );
						move_pos( buff_stream, 11 );
						char end = buff_stream.get();
						if( ( end != US ) && ( end != ETX ) )
							throw std::exception();
						if( end == ETX )
						{
							buff_msg_vector.push_back( buff_msg );
							break;
						}
						buff_msg_vector.push_back( buff_msg );
						continue;
					}
					throw std::exception();
				}
				size_t length = buff_msg_vector.size();
				for( size_t i = 0; i < length; i++ )
				{
					{
						boost::mutex::scoped_lock lock( lock_output_ );
						output_ << "Q " << std::fixed;
						size_t j = 0;
						size_t curr_size = buff_msg_vector[i].security_symbol().size();
						while( ( j != curr_size ) && ( buff_msg_vector[i].security_symbol()[j] != (char)32 ) )
						{
							output_ << buff_msg_vector[i].security_symbol()[j];
							j++;
						}
						output_ << " " << std::setprecision( 2 ) << buff_msg_vector[i].bid_price() << " " << std::setprecision( 1 ) << buff_msg_vector[i].bid_volume() << " " << std::setprecision( 2 ) << buff_msg_vector[i].offer_price() << " " << std::setprecision ( 1 ) << buff_msg_vector[i].offer_volume() <<"\n";
					}
					trade_message_ptr tr_msg( new trade_message() );
					quote_message_ptr qu_msg( new quote_message( buff_msg_vector[i] ) );
					market_data_processor::union_message u_m( false, tr_msg, qu_msg );
					{
						boost::unique_lock< boost::mutex > lock( market_data_processor::lock_union_message_queue_access );
						processor_.union_message_queue.push( u_m );
						market_data_processor::union_message_queue_cond_var.notify_one();
						lock.unlock();
					}
				}
			}
		}
		catch( std::exception invalid_block )
		{
			continue;
		}
	}
}