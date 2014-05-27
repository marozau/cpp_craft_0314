#include "trade_message.h"

multicast_communication::trade_message::trade_message() : _security_symbol("")
{
	_price = 0.0;
	_volume = 0.0;
}

multicast_communication::trade_message::trade_message(std::string _timestamp, std::string _security_symbol, double _price, double _volume) : 
	_timestamp(_timestamp), _security_symbol(_security_symbol), _price(_price), _volume(_volume)
{

}

std::string multicast_communication::trade_message::timestamp() const
{
	return _timestamp;
}

std::string multicast_communication::trade_message::security_symbol() const
{
	return _security_symbol;
}

double multicast_communication::trade_message::price() const
{
	return _price;
}

double multicast_communication::trade_message::volume() const
{
	return _volume;
}
