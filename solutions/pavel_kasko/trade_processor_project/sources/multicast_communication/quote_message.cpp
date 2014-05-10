#include "quote_message.h"

multicast_communication::quote_message::quote_message() : _security_symbol("")
{
	_bid_price = 0.0;
	_bid_volume = 0.0;
	_offer_price = 0.0;
	_offer_volume = 0.0;
}

multicast_communication::quote_message::quote_message(std::string _timestamp, std::string _security_symbol, double _bid_price, double _bid_volume, double _offer_price, double _offer_volume) : 
	_timestamp(_timestamp), _security_symbol(_security_symbol), _bid_price(_bid_price), _bid_volume(_bid_volume), _offer_price(_offer_price), _offer_volume(_offer_volume)
{

}

std::string multicast_communication::quote_message::timestamp() const
{
	return _timestamp;
}

std::string multicast_communication::quote_message::security_symbol() const
{
	return _security_symbol;
}

double multicast_communication::quote_message::bid_price() const
{
	return _bid_price;
}

double multicast_communication::quote_message::bid_volume() const
{
	return _bid_volume;
}

double multicast_communication::quote_message::offer_price() const
{
	return _offer_price;
}

double multicast_communication::quote_message::offer_volume() const
{
	return _offer_volume;
}
