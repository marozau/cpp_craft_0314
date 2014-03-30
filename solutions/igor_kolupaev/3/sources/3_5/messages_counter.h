#pragma once

#include <map>

#include "market_message.h"

struct messages_data_t
{
	uint32_t messages_num;
	uint32_t time_num;

	messages_data_t();

	double average() const;
};

typedef std::map<uint32_t, messages_data_t> msg_map_t;
typedef std::map<uint32_t, uint32_t> time_counter_t;

class messages_counter
{
public:
	void merge( const time_counter_t& second_counter );
	void inc_time( const uint32_t message_type );
	void add_count( const uint32_t message_type, const uint32_t number );
	void output_avg( std::ostream& out ) const;

private: 
	msg_map_t _data;
};

