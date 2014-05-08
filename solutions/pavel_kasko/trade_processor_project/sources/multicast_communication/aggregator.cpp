#include "aggregator.h"

namespace multicast_communication
{
	aggregator::aggregator()
	{
		end = false;
	}

	void aggregator::SaveOne(std::string new_data, message_type type)
	{
		if (type == message_type::QUOTE)
			quote_data.push(new_data);
		else
			trade_data.push(new_data);
	}

	void aggregator::StartOutput()
	{
		boost::thread_group threads;

		threads.create_thread(boost::bind(&aggregator::QuoteOutput, this));
		threads.create_thread(boost::bind(&aggregator::TradeOutput, this));
		threads.join_all();
	}

	void aggregator::StopOutput()
	{
		end = true;
	}

	void aggregator::QuoteOutput()
	{
		converter conv;
		while (!end || !quote_data.IsEmpty())
		{
			conv.ConvertToQuote(quote_data.pop());
		}
	}

	void aggregator::TradeOutput()
	{
		converter conv;
		while (!end || !trade_data.IsEmpty())
		{
			conv.ConvertToTrade(trade_data.pop());
		}
	}
}
