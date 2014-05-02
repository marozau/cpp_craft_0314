#ifndef _MINUTE_CALCULATOR_MINUTE_CALCULATOR_H
#define _MINUTE_CALCULATOR_MINUTE_CALCULATOR_H

#include <trade_message.h>
#include <quote_message.h>
#include <market_data_processor.h>


#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace minute_calculator{

	static const double EPS = 0.001;

	class minute_datafeed{
	public:

		boost::uint32_t minute;
		char stock_name[16];
		double open_price;
		double high_price;
		double low_price;
		double close_price;
		double volume;
		double bid;
		double ask;

		minute_datafeed(){
			stock_name[0] = '\0';
		}

		minute_datafeed( std::string stock_name_ ){
			strcpy( stock_name, stock_name_.c_str() );
		}

		bool operator  == ( const minute_datafeed & data){

			return (		abs(ask - data.ask)<EPS &&
							abs(bid - data.bid)<EPS &&
							abs(close_price - data.close_price)<EPS &&
							abs(high_price  - data.high_price)<EPS &&
							abs(low_price - data.low_price)<EPS &&
							minute == data.minute &&
							abs(open_price  - data.open_price)<EPS &&
							abs(volume - data.volume)<EPS);
		}

		minute_datafeed & operator = (const minute_datafeed & data){
					if (this == &data) return (*this);

					strcpy( stock_name, data.stock_name );
					ask = data.ask;
					bid = data.bid;
					close_price = data.close_price;
					high_price  = data.high_price;
					low_price = data.low_price;
					minute  = data.minute;
					open_price  = data.open_price;
					volume = data.volume;

					return *this;
		}

	};

	typedef boost::shared_ptr< minute_datafeed > minute_datafeed_ptr;

	
	class calculator: public multicast_communication::market_data_processor{
		private:
			
			typedef boost::function< void ( const minute_datafeed_ptr& datafeed ) > calc_call;
			enum full_datafeed { only_quote, only_trade, full};

			calc_call callback_ñ;
			std::map < std::string, minute_datafeed_ptr > data_all;
			std::map < std::string, full_datafeed>  data_full;

		public:

			explicit calculator( calc_call handler );
			virtual ~calculator();

			void new_trade( const multicast_communication::trade_message_ptr& );
			void new_quote( const multicast_communication::quote_message_ptr& );
	};

}

#endif //_MINUTE_CALCULATOR_MINUTE_CALCULATOR_H