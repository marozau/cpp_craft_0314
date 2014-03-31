#include "stock_data.h"
#include "read_and_write.h"
#include <boost/cstdint.hpp>

namespace myConst{
	const boost::uint32_t oneYear = 372;
	const boost::uint32_t oneMonth = 31;
}

binary_reader::stock_data::stock_data(std::ifstream& input)
{
	read_and_write::read_binary(input, stock_name_);
	read_and_write::read_binary(input, date_time_);
	read_and_write::read_binary(input, price_);
	read_and_write::read_binary(input, vwap_);
	read_and_write::read_binary(input, volume_);
	read_and_write::read_binary(input, f1_);
	read_and_write::read_binary(input, t1_);
	read_and_write::read_binary(input, f2_);
	read_and_write::read_binary(input, f3_);
	read_and_write::read_binary(input, f4_);
}

binary_reader::stock_data::stock_data(const char* stock_name,
							const char* date_time,
							const double price,
							const double vwap,
							const boost::uint32_t volume,
							const double f1,
							const double t1,
							const double f2,
							const double f3,
							const double f4)
	: price_(price), vwap_(vwap), volume_(volume)
	, f1_(f1), t1_(t1), f2_(f2), f3_(f3), f4_(f4)
{
	memcpy(stock_name_, stock_name, sizeof(stock_name_));
	memcpy(date_time_, date_time, sizeof(date_time_));
}

binary_reader::stock_data::~stock_data()
{
}

void binary_reader::stock_data::write(std::ofstream& output)
{
	static char stock_name[9];
	memcpy(stock_name, stock_name_, sizeof(stock_name_));
	
	int day;
	int year;
	int month;
	sscanf(date_time_, "%4d%2d%2d", &year, &month, &day);
	boost::uint32_t date = (year - 1) * myConst::oneYear + (month - 1)* myConst::oneMonth + day;
	
	read_and_write::write_binary(output, stock_name);
	read_and_write::write_binary(output, date);
	read_and_write::write_binary(output, vwap_);
	read_and_write::write_binary(output, volume_);
	read_and_write::write_binary(output, f2_);
}

void binary_reader::stock_data::write_raw(std::ofstream& output)
{	
	read_and_write::write_binary(output, stock_name_);
	read_and_write::write_binary(output, date_time_);
	read_and_write::write_binary(output, price_);
	read_and_write::write_binary(output, vwap_);
	read_and_write::write_binary(output, volume_);
	read_and_write::write_binary(output, f1_);
	read_and_write::write_binary(output, t1_);
	read_and_write::write_binary(output, f2_);
	read_and_write::write_binary(output, f3_);
	read_and_write::write_binary(output, f4_);
}
