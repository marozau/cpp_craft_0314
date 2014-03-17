#include "stock_data.h"
#include "read_write_impl.h"
#include <string>

binary_reader::stock_data::stock_data( std::ifstream& in )
{
	read_write_impl::read(in, stock_name_, 8);
	read_write_impl::read(in, date_time_, 8);
	read_write_impl::read(in, price_);
	read_write_impl::read(in, vwap_);
	read_write_impl::read(in, volume_);
	read_write_impl::read(in, f1_);
	read_write_impl::read(in, t1_);
	read_write_impl::read(in, f2_);
	read_write_impl::read(in, f3_);
	read_write_impl::read(in, f4_);
}
binary_reader::stock_data::stock_data(const char* stock_name, const char* date_time, const double price, const double vwap,
	const boost::uint32_t volume, const double f1, const double t1, const double f2, const double f3, const double f4) :
	price_(price), vwap_(vwap), volume_(volume), f1_(f1), t1_(t1), f2_(f2),
	f3_(f3), f4_(f4)
{
	strncpy(stock_name_, stock_name, 8);
	strncpy(date_time_, date_time, 8);
}

void binary_reader::stock_data::write(std::ofstream& out) const
{
	using namespace std;
	read_write_impl::write(out, stock_name_, 8);
	read_write_impl::write(out, '\0');
	string yearS;
	yearS += date_time_[0];
	yearS += date_time_[1];
	yearS += date_time_[2];
	yearS += date_time_[3];
	string monthS;
	monthS += date_time_[4];
	monthS += date_time_[5];
	string dayS;
	dayS += date_time_[6];
	dayS += date_time_[7];
	int year = stoi(yearS);
	int month = stoi(monthS);
	int day = stoi(dayS);
	boost::uint32_t date = (year - 1) * 372 + (month - 1) * 31 + day;
	read_write_impl::write(out, date);
	read_write_impl::write(out, vwap_);
	read_write_impl::write(out, volume_);
	read_write_impl::write(out, f2_);
}

size_t binary_reader::stock_data::size() const
{
	return 76;
}
