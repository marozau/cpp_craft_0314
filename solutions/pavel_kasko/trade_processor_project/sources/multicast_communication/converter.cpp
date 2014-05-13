#include "converter.h"
#include <boost\lexical_cast.hpp>
#include <boost\make_shared.hpp>

namespace multicast_communication
{
	converter::converter() : SOH(0x01), US(0x1F), ETX(0x03)
	{		
	}

	std::vector<quote_message_ptr>* converter::ConvertToQuote(std::string& input)
	{
		size_t pos = 0;

		if (input[pos++] != SOH)
			throw std::logic_error("Invalid input message: " + input);

		char message_category = input[pos++];
		char message_type = input[pos++];
		
		std::vector<quote_message_ptr>* res = new std::vector<quote_message_ptr>();
		
		if (message_category == 'E')
		{
			pos += 16; // timestamp position (need 5 more);
			std::string timestamp = input.substr(pos, 6);

			pos += 6; //message first position security symbol

			while (pos < input.length() && input[pos] != ETX)
			{
				if (message_type == 'B') //B = long
				{
					quote_message_ptr message = quote_message_ptr(GetLongQuoteMessage(input, pos, timestamp));
					(*res).push_back(message);
				}
				else if (message_type == 'D') //D = short
				{
					quote_message_ptr message = quote_message_ptr(GetShortQuoteMessage(input, pos, timestamp));
					(*res).push_back(message);
				}
			
				char tmp = input[pos];

				if(input[pos] == US)
					pos++; //first position of next message
				else
					break;
			}
		}

		return res;
	}

	std::vector<trade_message_ptr>* converter::ConvertToTrade(std::string& input)
	{
		size_t pos = 0;

		if (input[pos++] != SOH)
			throw std::logic_error("Invalid input message: " + input);

		char message_category = input[pos++];
		char message_type = input[pos++];

		std::vector<trade_message_ptr>* res = new std::vector<trade_message_ptr>();
		
		if (message_category == 'E')
		{
			pos += 16; // timestamp position (need 5 more);
			std::string timestamp = input.substr(pos, 6);
			pos += 6; //message first position security symbol

			while (pos < input.length() && input[pos] != ETX)
			{
				if (message_type == 'B') //B = long
				{
					trade_message_ptr message = trade_message_ptr(GetLongTradeMessage(input, pos, timestamp));
					(*res).push_back(message);
				}
				else if (message_type == 'I') //I = short
				{
					trade_message_ptr message = trade_message_ptr(GetShortTradeMessage(input, pos, timestamp));
					(*res).push_back(message);
				}

				char tmp = input[pos];

				if(input[pos] == US)
					pos++; //first position of next message
				else
					break;
			}	
		}
		
		return res;
	}

	void converter::ConvertToQuote(std::string& input, boost::function<void(quote_message_ptr)> out_f)
	{
		size_t pos = 0;

		if (input[pos++] != SOH)
			return;

		char message_category = input[pos++];
		char message_type = input[pos++];
			
		if (message_category != 'E')
			return;

		pos += 16; // timestamp position (need 5 more);
		std::string timestamp = input.substr(pos, 6);
		pos += 6; //message first position security symbol

		while (pos < input.length() && input[pos] != ETX)
		{
			if (message_type == 'B') //B = long
			{
				quote_message_ptr message = quote_message_ptr(GetLongQuoteMessage(input, pos, timestamp));
				out_f(message);
			}
			else if (message_type == 'D') //D = short
			{
				quote_message_ptr message = quote_message_ptr(GetShortQuoteMessage(input, pos, timestamp));
				out_f(message);
			}
			
			char tmp = input[pos];

			if(input[pos] == US)
				pos++; //first position of next message
			else
				break;
		}
	}

	void converter::ConvertToTrade(std::string& input, boost::function<void(trade_message_ptr)> out_f)
	{
		size_t pos = 0;

		if (input[pos++] != SOH)
			return;

		char message_category = input[pos++];
		char message_type = input[pos++];

		if (message_category != 'E')
			return;

		pos += 16; // timestamp position (need 5 more);
		std::string timestamp = input.substr(pos, 6);
		pos += 6; //message first position security symbol

		while (pos < input.length() && input[pos] != ETX)
		{
			if (message_type == 'B') //B = long
			{
				trade_message_ptr message = trade_message_ptr(GetLongTradeMessage(input, pos, timestamp));
				out_f(message);
			}
			else if (message_type == 'I') //I = short
			{
				trade_message_ptr message = trade_message_ptr(GetShortTradeMessage(input, pos, timestamp));
				out_f(message);
			}

			char tmp = input[pos];

			if(input[pos] == US)
				pos++; //first position of next message
			else
				break;
		}
	}

	trade_message* converter::GetShortTradeMessage(std::string& input, size_t& pos, std::string& timestamp)
	{
		try
		{
			std::string security_symbol = input.substr(pos, 3);
			security_symbol.erase(std::remove(security_symbol.begin(), security_symbol.end(), ' '), security_symbol.end());

			pos += 3;
			pos += 1;
			std::string short_trade_vol = input.substr(pos, 4);
			double trade_vol = boost::lexical_cast<double>(short_trade_vol);

			pos += 4;
			pos += 1;
			std::string short_trade_price = input.substr(pos, 8);
			double trade_price = boost::lexical_cast<double>(short_trade_price);

			pos += 8;
			pos += 3;

			return new trade_message(timestamp, security_symbol, trade_price, trade_vol);
		}
		catch(boost::bad_lexical_cast)
		{
			throw std::logic_error("Invalid input message: " + input);
		}
	}

	trade_message* converter::GetLongTradeMessage(std::string& input, size_t& pos, std::string& timestamp)
	{
		try
		{
			std::string security_symbol = input.substr(pos, 11);
			security_symbol.erase(std::remove(security_symbol.begin(), security_symbol.end(), ' '), security_symbol.end());

			pos += 11;
			pos += 22;
			std::string long_trade_price = input.substr(pos, 12);
			double trade_price = boost::lexical_cast<double>(long_trade_price);

			pos += 12;
			std::string long_trade_vol = input.substr(pos, 9);
			double trade_vol = boost::lexical_cast<double>(long_trade_vol);

			pos += 9;
			pos += 4;

			return new trade_message(timestamp, security_symbol, trade_price, trade_vol);
		}
		catch(boost::bad_lexical_cast)
		{
			throw std::logic_error("Invalid input message: " + input);
		}
	}

	quote_message* converter::GetLongQuoteMessage(std::string& input, size_t& pos, std::string& timestamp)
	{
		try
		{
			std::string sequrity_symbol = input.substr(pos, 11);

			pos += 28;
			std::string bid_long_price = input.substr(pos, 12);
			double bid_price = boost::lexical_cast<double>(bid_long_price);

			pos += 12;
			std::string bid_long_size = input.substr(pos, 7);
			double bid_size = boost::lexical_cast<double>(bid_long_size);

			pos += 8;
			std::string offer_long_price = input.substr(pos, 12);
			double offer_price = boost::lexical_cast<double>(offer_long_price);

			pos += 12;
			std::string offer_long_size = input.substr(pos, 7);
			double offer_size = boost::lexical_cast<double>(offer_long_size);

			pos += 7;
			pos += 11;
			
			return new quote_message(timestamp, sequrity_symbol, bid_price, bid_size, offer_price, offer_size);
		}
		catch(boost::bad_lexical_cast)
		{
			throw std::logic_error("Invalid input message: " + input);
		}
	}

	quote_message* converter::GetShortQuoteMessage(std::string& input, size_t& pos, std::string& timestamp)
	{
		try
		{
			std::string sequrity_symbol = input.substr(pos, 3);
				
			pos += 7; //bid short prise first position
			std::string bid_short_price = input.substr(pos, 8);
			double bid_price = boost::lexical_cast<double>(bid_short_price);
				
			pos += 8; // bid size first position
			std::string bid_short_size = input.substr(pos, 3);
			double bid_size = boost::lexical_cast<double>(bid_short_size);

			pos += 5;
			std::string offer_short_price = input.substr(pos, 8);
			double offer_price = boost::lexical_cast<double>(offer_short_price);

			pos += 8;
			std::string offer_short_size = input.substr(pos, 3);
			double offer_size = boost::lexical_cast<double>(offer_short_size);
		
			pos += 3;
			pos += 3;
			
			return new quote_message(timestamp, sequrity_symbol, bid_price, bid_size, offer_price, offer_size);
		}
		catch(boost::bad_lexical_cast)
		{
			throw std::logic_error("Invalid input message: " + input);
		}		
	}
}