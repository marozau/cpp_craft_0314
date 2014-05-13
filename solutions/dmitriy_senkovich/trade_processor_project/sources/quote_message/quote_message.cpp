#include "quote_message.h"

using namespace trade_processor_project;

quote_message::quote_message() 
		:if_long( false )
		,security_symbol_( "\0" )
		,bid_price_( 0 )
		,bid_price_denominator_indicator_( "\0" )
		,bid_size_of_units_of_trade_( 0 )
		,offer_price_( 0 )
		,offer_price_denominator_indicator_( "\0" )
		,offer_size_of_units_of_trade_( 0 )
		,lower_limit_price_band_denominator_indicator_( "\0" )
		,lower_limit_price_band_( 0 )
		,bid_size_in_units_of_trade_( 0 )
		,upper_limit_price_band_denominator_indicator_( "\0" )
		,upper_limit_price_band_( 0 )
		,offer_size_in_units_of_trade_( 0 )
		,minute_( 0 )
{	
}
std::string quote_message::security_symbol() const
{
	return security_symbol_;
}
double quote_message::bid_price() const
{
	if ( if_long )
		return lower_limit_price_band_;
	else 
		return bid_price_;
}
double quote_message::bid_volume() const
{
	if( if_long )
		return bid_size_in_units_of_trade_;
	else
		return bid_size_of_units_of_trade_;
}
double quote_message::offer_price() const
{
	if( if_long )
		return upper_limit_price_band_;
	else
		return offer_price_;
}
double quote_message::offer_volume() const
{
	if( if_long )
		return offer_size_in_units_of_trade_;
	else
		return offer_size_of_units_of_trade_;
}
std::string quote_message::bid_price_denominator_indicator() const
{
	return bid_price_denominator_indicator_;
}
std::string quote_message::offer_price_denominator_indicator() const
{
	return offer_price_denominator_indicator_;
}
std::string quote_message::lower_limit_price_band_denominator_indicator() const
{
	return lower_limit_price_band_denominator_indicator_;
}
std::string quote_message::upper_limit_price_band_denominator_indicator() const
{
	return upper_limit_price_band_denominator_indicator_;
}
boost::uint32_t quote_message::minute() const
{
	return minute_;
}
std::string& quote_message::set_security_symbol()
{
	return security_symbol_;
}
double& quote_message::set_bid_price()
{
	return bid_price_;
}
std::string& quote_message::set_bid_price_denominator_indicator()
{
	return bid_price_denominator_indicator_;
}
double& quote_message::set_bid_size_of_units_of_trade()
{
	return bid_size_of_units_of_trade_;
}
double& quote_message::set_offer_price()
{
	return offer_price_;
}
std::string& quote_message::set_offer_price_denominator_indicator()
{
	return offer_price_denominator_indicator_;
}
double& quote_message::set_offer_size_of_units_of_trade()
{
	return offer_size_of_units_of_trade_;
}
std::string& quote_message::set_lower_limit_price_band_denominator_indicator()
{
	return lower_limit_price_band_denominator_indicator_;
}
double& quote_message::set_lower_limit_price_band()
{
	return lower_limit_price_band_;
}
double& quote_message::set_bid_size_in_units_of_trade()
{
	return bid_size_in_units_of_trade_;
}
std::string& quote_message::set_upper_limit_price_band_denominator_indicator()
{
	return upper_limit_price_band_denominator_indicator_;
}
double& quote_message::set_upper_limit_price_band()
{
	return upper_limit_price_band_;
}
double& quote_message::set_offer_size_in_units_of_trade()
{
	return offer_size_in_units_of_trade_;
}
boost::uint32_t& quote_message::set_minute()
{
	return minute_;
}