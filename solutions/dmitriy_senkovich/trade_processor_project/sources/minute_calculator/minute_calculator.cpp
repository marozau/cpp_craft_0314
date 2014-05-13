#include "minute_calculator.h"

using namespace trade_processor_project;

bool minute_calculator::to_stop = false;
boost::mutex minute_calculator::lock_to_stop;
boost::thread minute_calculator::start_thread_;

minute_calculator::minute_calculator( market_data_processor& processor )
	:processor_( processor )
{
}
void minute_calculator::calculating( const market_data_processor::union_message& um )
{
	if( um.trade )
	{
		trade_message tm = *um.tr_msg;
		if( minute_datafeed_[tm.security_symbol()].minute == -1 )
		{
			minute_datafeed_[tm.security_symbol()].minute = tm.minute();
			minute_datafeed_[tm.security_symbol()].seconds = tm.minute() * 60;
			size_t j = 0;
			size_t curr_size = tm.security_symbol().size();
			while( ( j != curr_size ) && ( tm.security_symbol()[j] != (char)32 ) )
			{
				minute_datafeed_[tm.security_symbol()].stock_name[j] = tm.security_symbol()[j];
				j++;
			}
			minute_datafeed_[tm.security_symbol()].stock_name[j] = '\0';
			minute_datafeed_[tm.security_symbol()].open_price = tm.price();
			minute_datafeed_[tm.security_symbol()].close_price = tm.price();
			minute_datafeed_[tm.security_symbol()].low_price = tm.price();
			minute_datafeed_[tm.security_symbol()].high_price = tm.price();
			minute_datafeed_[tm.security_symbol()].volume = tm.volume();
			return;
		}
		if( tm.minute() > minute_datafeed_[tm.security_symbol()].minute )
		{
			{
				boost::unique_lock< boost::mutex > lock( market_data_processor::lock_datafeed_queue_access );
				processor_.datafeed_queue.push( minute_datafeed_[tm.security_symbol()] );
				market_data_processor::datafeed_queue_cond_var.notify_one();
				lock.unlock();
			}
			minute_datafeed_[tm.security_symbol()].minute = tm.minute();
			minute_datafeed_[tm.security_symbol()].seconds = tm.minute() * 60;
			minute_datafeed_[tm.security_symbol()].open_price = tm.price();
			minute_datafeed_[tm.security_symbol()].close_price = tm.price();
			minute_datafeed_[tm.security_symbol()].low_price = tm.price();
			minute_datafeed_[tm.security_symbol()].high_price = tm.price();
			minute_datafeed_[tm.security_symbol()].volume = tm.volume();
			minute_datafeed_[tm.security_symbol()].bid = 0;
			minute_datafeed_[tm.security_symbol()].ask = 0;
			return;
		}
		if( tm.minute() < minute_datafeed_[tm.security_symbol()].minute )
			return;
		minute_datafeed_[tm.security_symbol()].close_price = tm.price();
		if( minute_datafeed_[tm.security_symbol()].low_price > tm.price() )
			minute_datafeed_[tm.security_symbol()].low_price = tm.price();
		if( minute_datafeed_[tm.security_symbol()].high_price < tm.price() )
			minute_datafeed_[tm.security_symbol()].high_price = tm.price();
		minute_datafeed_[tm.security_symbol()].volume += tm.volume();
	}
	else
	{
		quote_message qm = *um.qu_msg;
		if( minute_datafeed_[qm.security_symbol()].minute == -1 )
		{
			minute_datafeed_[qm.security_symbol()].minute = qm.minute();
			minute_datafeed_[qm.security_symbol()].seconds = qm.minute() * 60;
			size_t j = 0;
			size_t curr_size = qm.security_symbol().size();
			while( ( j != curr_size ) && ( qm.security_symbol()[j] != (char)32 ) )
			{
				minute_datafeed_[qm.security_symbol()].stock_name[j] = qm.security_symbol()[j];
				j++;
			}
			minute_datafeed_[qm.security_symbol()].stock_name[j] = '\0';
			minute_datafeed_[qm.security_symbol()].bid = qm.bid_volume();
			minute_datafeed_[qm.security_symbol()].ask = qm.offer_volume();
			return;
		}
		if( qm.minute() > minute_datafeed_[qm.security_symbol()].minute )
		{
			{
				boost::unique_lock< boost::mutex > lock( market_data_processor::lock_datafeed_queue_access );
				processor_.datafeed_queue.push( minute_datafeed_[qm.security_symbol()] );
				market_data_processor::datafeed_queue_cond_var.notify_one();
				lock.unlock();
			}
			minute_datafeed_[qm.security_symbol()].minute = qm.minute();
			minute_datafeed_[qm.security_symbol()].seconds = qm.minute() * 60;
			minute_datafeed_[qm.security_symbol()].open_price = 0;
			minute_datafeed_[qm.security_symbol()].close_price = 0;
			minute_datafeed_[qm.security_symbol()].low_price = 0;
			minute_datafeed_[qm.security_symbol()].high_price = 0;
			minute_datafeed_[qm.security_symbol()].volume = 0;
			minute_datafeed_[qm.security_symbol()].bid = qm.bid_volume();
			minute_datafeed_[qm.security_symbol()].ask = qm.offer_volume();
			return;
		}
		if( qm.minute() < minute_datafeed_[qm.security_symbol()].minute )
			return;
		minute_datafeed_[qm.security_symbol()].bid += qm.bid_volume();
		minute_datafeed_[qm.security_symbol()].ask += qm.offer_volume();
	}
}
void minute_calculator::begin()
{
	while( true )
	{
		market_data_processor::union_message um;
		{
			boost::unique_lock< boost::mutex > lock( market_data_processor::lock_union_message_queue_access );
			while( processor_.union_message_queue.empty() )
			{
				{
					boost::mutex::scoped_lock lock( minute_calculator::lock_to_stop );
					if( minute_calculator::to_stop )
						return;
				}
				market_data_processor::union_message_queue_cond_var.wait( lock );
			}
			{
				boost::mutex::scoped_lock lock( minute_calculator::lock_to_stop );
				if( minute_calculator::to_stop )
				{
					if( processor_.union_message_queue.empty() )
						return;
					stop_calculating();
					return;
				}
			}
			um = processor_.union_message_queue.front();
			processor_.union_message_queue.pop();
			lock.unlock();
		}

		calculating( um );
	}
}
void minute_calculator::start()
{
	start_thread_ = boost::thread( boost::bind( &minute_calculator::begin, this ) );
	start_thread_.join();
}
void minute_calculator::stop_calculating()
{
	while( !processor_.union_message_queue.empty() )
	{
		market_data_processor::union_message um;
		um = processor_.union_message_queue.front();
		processor_.union_message_queue.pop();
		
		calculating( um );
	}
}
void minute_calculator::stop()
{
	{
		boost::mutex::scoped_lock lock( minute_calculator::lock_to_stop );
		minute_calculator::to_stop = true;
	}
	market_data_processor::union_message_queue_cond_var.notify_one();
	start_thread_.join();
}