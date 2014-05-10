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

	public:
		data_feed(std::uint32_t, std::string, double open_price);

		void SetHighPrice(double value);
		void SetLowPrice(double value);
		void SetClosePrice(double value);
		
		void IncreaseVolume(double value);
		void IncreaseAsk(double value);
		void IncreaseBid(double value);
	};
}

#endif //DATA_FEED