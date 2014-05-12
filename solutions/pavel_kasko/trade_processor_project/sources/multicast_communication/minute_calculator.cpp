#include "minute_calculator.h"
#include <vector>
#include <boost\lexical_cast.hpp>

namespace multicast_communication
{
	minute_calculator::minute_calculator() : time_dec_dif(48), quote_flushed(false), trade_flushed(false)
	{

	}

	minute_calculator::~minute_calculator()
	{
		for(auto i = d_feeds.begin(); i != d_feeds.end(); ++i)
		{
			(*(*i).second).Print();
			delete (*i).second;
		}
	}

	void minute_calculator::SaveOne(std::string& input, message_type type)
	{
		boost::mutex::scoped_lock lock(locker);
		
		if(type == message_type::QUOTE)
		{
			try
			{
				auto v = _cnv.ConvertToQuote(input);

				for(auto i = (*v).begin(); i != (*v).end(); ++i)
					SaveQuote(*i);
				
				delete v;
			}
			catch(std::logic_error e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else
		{
			try
			{
				auto v = _cnv.ConvertToTrade(input);

				for(auto i = (*v).begin(); i != (*v).end(); ++i)
					SaveTrade(*i);

				delete v;
			}
			catch(std::logic_error e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}

	void minute_calculator::SaveTrade(trade_message_ptr trade)
	{
		std::string sec_symbol = (*trade).security_symbol();
		sec_symbol.erase(std::remove(sec_symbol.begin(), sec_symbol.end(), '/'), sec_symbol.end());

		std::uint32_t minute = GetMinute((*trade).timestamp());

		if(d_feeds.find(sec_symbol) == d_feeds.end())
		{
			std::uint32_t s_1990 = Get1990Seconds((*trade).timestamp());

			data_feed* _data_feed = new data_feed(s_1990, sec_symbol);
			(*_data_feed).SetOpenPrice((*trade).price());
			(*_data_feed).SetHighPrice((*trade).price());
			(*_data_feed).SetLowPrice((*trade).price());
			(*_data_feed).SetTradeMinute(minute);

			d_feeds[sec_symbol] = _data_feed;
		}
		else if((*d_feeds[sec_symbol]).tradeMinute() != minute)
		{
			(*d_feeds[sec_symbol]).SetTradeMinute(minute);

			(*d_feeds[sec_symbol]).PrintTradePart(quote_flushed);
			trade_flushed = true;
			
			(*d_feeds[sec_symbol]).ResetTradePart();

			(*d_feeds[sec_symbol]).SetOpenPrice((*trade).price());
			
			std::uint32_t s_1990 = Get1990Seconds((*trade).timestamp());
			(*d_feeds[sec_symbol]).SetMinute(s_1990);
			
			if(quote_flushed)
			{
				quote_flushed = trade_flushed =  false;
			}				
		}

		if((*d_feeds[sec_symbol]).tradeMinute() == minute)
		{
			(*d_feeds[sec_symbol]).IncreaseVolume((*trade).volume());
			
			if((*d_feeds[sec_symbol]).highPrice() < (*trade).price())
				(*d_feeds[sec_symbol]).SetHighPrice((*trade).price());

			else if((*d_feeds[sec_symbol]).lowPrice() > (*trade).price())
				(*d_feeds[sec_symbol]).SetLowPrice((*trade).price());

			(*d_feeds[sec_symbol]).SetClosePrice((*trade).price());
		}
	}

	void minute_calculator::SaveQuote(quote_message_ptr quote)
	{
		std::string sec_symbol = (*quote).security_symbol();
		sec_symbol.erase(std::remove(sec_symbol.begin(), sec_symbol.end(), '/'), sec_symbol.end());

		std::uint32_t minute = GetMinute((*quote).timestamp());

		if(d_feeds.find(sec_symbol) == d_feeds.end())
		{
			std::uint32_t s_1990 = Get1990Seconds((*quote).timestamp());
			
			data_feed* _data_feed = new data_feed(s_1990, sec_symbol);
			(*_data_feed).SetQuoteMinute(minute);

			d_feeds[sec_symbol] = _data_feed;
		}
		else if((*d_feeds[sec_symbol]).quoteMinure() != minute)
		{
			(*d_feeds[sec_symbol]).SetQuoteMinute(minute);
			
			(*d_feeds[sec_symbol]).PrintQuotePart(trade_flushed);
			quote_flushed = true;
			
			(*d_feeds[sec_symbol]).ResetQuotePart();

			if(trade_flushed)
			{
				quote_flushed = trade_flushed =  false;
			}
		}

		if((*d_feeds[sec_symbol]).quoteMinure() == minute)
		{
			(*d_feeds[sec_symbol]).IncreaseAsk((*quote).offer_price());
			(*d_feeds[sec_symbol]).IncreaseBid((*quote).bid_price());
		}
	}

	std::uint32_t minute_calculator::GetMinute(std::string timestamp)
	{
		int m = ((int)timestamp[1]) - time_dec_dif;
		return m;
	}
	
	std::uint32_t minute_calculator::Get1990Seconds(std::string timestamp)
	{
		auto now = Clock::now();
		std::time_t now_c = Clock::to_time_t(now);
		struct tm *local_t = std::localtime(&now_c);
		
		int y = local_t->tm_year;
		int mon = local_t->tm_mon;
		int day = local_t->tm_mday;
		int h = ((int)timestamp[0]) - time_dec_dif;
		int m = ((int)timestamp[1]) - time_dec_dif;
		int s = ((int)timestamp[2]) - time_dec_dif;

		tm start;
		start.tm_year = y;
		start.tm_mon = mon;
		start.tm_mday = day;
		start.tm_hour = h;
		start.tm_min = m;
		start.tm_sec = s;
		time_t tm1 = mktime(&start);

		return tm1;
	}
}
