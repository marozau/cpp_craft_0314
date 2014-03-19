#pragma once

#include <set>

#include "market_message.h"

class market_message_filter
{
public:
	const static uint32_t MARKET_OPEN = 1u;
	const static uint32_t TRADE = 2u;
	const static uint32_t QUOTE = 3u;
	const static uint32_t MARKET_CLOSE = 4u;

	market_message_filter();

	bool is_up_to_date( const binary_reader::market_message& message, uint32_t delay );
	bool is_type_ok( const binary_reader::market_message& message );
	void update_time( const binary_reader::market_message& message );
	uint32_t current_time() const;

private:
	uint32_t _current_time;
	std::set<uint32_t> _good_types;
};

