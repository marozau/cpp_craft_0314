#include "market_processor.h"
#include <boost\lexical_cast.hpp>

multicast_communication::processor::processor( std::string filename ) 
	: trade_callback( boost::bind( &multicast_communication::processor::new_trade, this, _1 ) )
	, quote_callback( boost::bind( &multicast_communication::processor::new_quote, this, _1 ) )
{
	out.open( boost::lexical_cast< std::string >( SOURCE_DIR ) + "/" + filename );
}

multicast_communication::processor::~processor()
{
	out.close();
}

void multicast_communication::processor::parse( std::string& message, message_type type )
{
	std::stringstream in( message );
	bool transfer = false;
	while( !in.eof() )
	{
		if( !transfer )
		{
			const char temp = static_cast< const char >( in.get() );
			if( in.eof() || !temp )
				break;
			if( temp != SOH )
				return;
			transfer = true;
		}
		else
		{
			if( type == TRADE )
			{
				trade_message_ptr msg( new trade_message( trade_callback ) );
				msg->parse( in );
			}
			else 
			{
				quote_message_ptr msg( new quote_message( quote_callback ) );
				msg->parse( in );
			}

			char after_message = static_cast< char >( in.get() );
			while( after_message != US || after_message != EOT )
			{
				after_message = static_cast< char >( in.get() );
				if( in.eof() )
					return;
			}

			if( after_message == EOT )
				transfer = false;
			else                                               
				return;
		}
	}
}

void multicast_communication::processor::new_trade( const trade_message_ptr& msg )
{
	boost::mutex::scoped_lock lock( output_mtx );
	out << "T " << msg->security_symbol() << std::fixed << std::setprecision( 2 ) << " " << msg->price() << " " << msg->volume() << "\n";
}

void multicast_communication::processor::new_quote( const quote_message_ptr& msg )
{
	boost::mutex::scoped_lock lock( output_mtx );
	out << "Q " << msg->security_symbol() << std::fixed << std::setprecision( 2 ) << " " << msg->bid_price()
		<< " " << msg->bid_volume() << "  " << msg->offer_price() << " " << msg->offer_volume() << "\n";
}