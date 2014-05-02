#include "minute_calculator.h"  

#include <climits>

minute_calculator::calculator::calculator( calc_call h ): callback_ñ( h ){
}

minute_calculator::calculator::~calculator(){
	std::map< std::string, minute_datafeed_ptr >::const_iterator it;
	std::map< std::string, full_datafeed >::const_iterator it_full;
	it_full = data_full.begin();
	for (it = data_all.begin(); it != data_all.end(); ++it ){
		if (it_full->second == only_quote){
			it->second->open_price = it->second->high_price = it->second->low_price = it->second->close_price = 0;
			it->second->volume = 0;
		}
		if (it_full->second == only_trade){
			it->second->ask = 0;
			it->second->bid = 0;
		}
		callback_ñ( it->second );
	}
}


void minute_calculator::calculator::new_trade( const multicast_communication::trade_message_ptr& m )
{
	const std::string stock_name = m->security_symbol();

	if ( data_all.count ( stock_name ) == 0 ) {
		data_full.insert ( std::make_pair( stock_name, only_trade));
		data_all.insert( std::make_pair( stock_name, minute_datafeed_ptr( new minute_datafeed( stock_name ) )) );
		data_all[stock_name]->open_price = m->price();
		data_all[stock_name]->high_price = m->price();
		data_all[stock_name]->low_price = m->price();
		data_all[stock_name]->close_price = m->price();
		data_all[stock_name]->volume = m->volume();
		data_all[stock_name]->minute = m ->minute();
		return;
	}

	if( m->minute() < data_all[stock_name]->minute )
		return;


	if (  m->minute() > data_all[stock_name]->minute ){

		if (data_full[stock_name] == only_quote){
			data_all[stock_name]->open_price = data_all[stock_name]->high_price = data_all[stock_name]->low_price = data_all[stock_name]->close_price = 0;
			data_all[stock_name]->volume = 0;
		}
		if (data_full[stock_name] == only_trade){
			data_all[stock_name]->ask = 0;
			data_all[stock_name]->bid = 0;
		}
		callback_ñ( data_all[stock_name] );

		data_full[stock_name] = only_trade;
		data_all[stock_name] = minute_datafeed_ptr( new minute_datafeed( stock_name ) );

		data_all[stock_name]->open_price = m->price();
		data_all[stock_name]->high_price = m->price();
		data_all[stock_name]->low_price = m->price();
		data_all[stock_name]->close_price = m->price();
		data_all[stock_name]->volume = m->volume();
		data_all[stock_name]->minute = m ->minute();

		return;
	}

	if( m->minute() == data_all[stock_name]->minute ){
		if (data_full[stock_name] == only_quote) {
			data_all[stock_name]->open_price = m->price();
			data_all[stock_name]->high_price = m->price();
			data_all[stock_name]->low_price = m->price();
			data_all[stock_name]->close_price = m->price();
			data_all[stock_name]->volume = 0;
			data_full[stock_name] = full;
		}
		else{
			data_all[stock_name]->high_price = std::max( data_all[stock_name]->high_price, m->price() );
			data_all[stock_name]->low_price = std::min( data_all[stock_name]->low_price, m->price() );
			data_all[stock_name]->close_price = m->price();
		}
		data_all[stock_name]->volume += m->volume();
	}
}

void minute_calculator::calculator::new_quote( const multicast_communication::quote_message_ptr& m ){
	
	const std::string stock_name = m->security_symbol();

	if ( data_all.count( stock_name ) == 0) {
		data_full.insert (std::make_pair(stock_name, only_quote));
		data_all.insert( std::make_pair( stock_name, minute_datafeed_ptr( new minute_datafeed( stock_name ) ) ) );
		data_all[stock_name]->ask = m->offer_volume();
		data_all[stock_name]->bid = m->bid_volume();
		data_all[stock_name]->minute = m ->minute();
		return;
	}

	if( m->minute() < data_all[stock_name]->minute )
		return;

	if (  m->minute() > data_all[stock_name]->minute ){
		if (data_full[stock_name] == only_quote){
			data_all[stock_name]->open_price = data_all[stock_name]->high_price = data_all[stock_name]->low_price = data_all[stock_name]->close_price = 0;
			data_all[stock_name]->volume = 0;
		}
		if (data_full[stock_name] == only_trade){
			data_all[stock_name]->ask = 0;
			data_all[stock_name]->bid = 0;
		}

		callback_ñ( data_all[stock_name] );

		data_all[stock_name] =  minute_datafeed_ptr( new minute_datafeed( stock_name ) );
		data_full[stock_name] = only_quote;
		data_all[stock_name]->ask = m->offer_volume();
		data_all[stock_name]->bid = m->bid_volume();
		data_all[stock_name]->minute = m ->minute();
		return;

	}

	if ( data_all[stock_name]->minute == m->minute() ){	
		if (data_full[stock_name] == only_trade){
			data_all[stock_name]->ask = 0;
			data_all[stock_name]->bid = 0;
			data_full[stock_name] = full;
		}
		data_all[stock_name]->ask += m->offer_volume();
		data_all[stock_name]->bid += m->bid_volume();
	}
}