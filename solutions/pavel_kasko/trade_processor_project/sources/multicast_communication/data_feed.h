#ifndef DATA_FEED
#define DATA_FEED

#include <cstdint>
#include <string>

namespace multicast_communication
{
	class data_feed
	{
		std::uint32_t minute;
		char stock_name[16];
		double open_price;
		double high_price;
		double low_price;
		double close_price;
		double voulme;
		double ask;
		double bid;

		std::uint32_t trade_minute;
		std::uint32_t quote_minure;

	public:
		data_feed(std::uint32_t, std::string);

		void SetHighPrice(double value);
		void SetLowPrice(double value);
		void SetClosePrice(double value);
		void SetOpenPrice(double value);
		void SetMinute(std::uint32_t);
		void SetQuoteMinute(std::uint32_t);
		void SetTradeMinute(std::uint32_t);
		
		void IncreaseVolume(double value);
		void IncreaseAsk(double value);
		void IncreaseBid(double value);

		double highPrice();
		double lowPrice();
		std::uint32_t tradeMinute();
		std::uint32_t quoteMinure();


		void Print();

		void PrintTradePart(bool);
		void PrintQuotePart(bool);

		void ResetTradePart();
		void ResetQuotePart();
	};
}

#endif //DATA_FEED