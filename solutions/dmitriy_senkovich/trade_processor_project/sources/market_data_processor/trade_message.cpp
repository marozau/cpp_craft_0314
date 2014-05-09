#include "trade_message.h"

using namespace trade_processor_project;

trade_message::trade_message()
		:security_symbol_( "\0" )
		,trade_volume_( 0 )
		,price_denominator_indicator_( "\0" )
		,trade_price_( 0 )
		,minute_( 0 )
{
}
std::string trade_message::security_symbol() const
{
	return security_symbol_;
}
double trade_message::price() const
{
	return trade_price_;
}
double trade_message::volume() const
{
	return trade_volume_;
}
std::string trade_message::price_denominator_indicator() const
{
	return price_denominator_indicator_;
}
boost::uint32_t trade_message::minute() const
{
	return minute_;
}
std::string& trade_message::set_security_symbol()
{
	return security_symbol_;
}
double& trade_message::set_trade_volume()
{
	return trade_volume_;
}
std::string& trade_message::set_price_denominator_indicator()
{
	return price_denominator_indicator_;
}
double& trade_message::set_trade_price()
{
	return trade_price_;
}
boost::uint32_t& trade_message::set_minute()
{
	return minute_;
}