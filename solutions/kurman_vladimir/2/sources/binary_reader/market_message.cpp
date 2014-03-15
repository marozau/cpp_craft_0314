#include "market_message.h"
#include "read_write_impl.h"
#include <cstring>

binary_reader::market_message::market_message( std::ifstream& in )
{
	read_write_impl::read(in, type_);
	read_write_impl::read(in, time_);
	read_write_impl::read(in, len_);
	msg_ = new char[len_];
	read_write_impl::read(in, msg_, len_);
}

binary_reader::market_message::market_message(const boost::uint32_t type, const boost::uint32_t time, const boost::uint32_t len,
	const char* const msg) : type_(type), time_(time), len_(len)
{
	msg_ = new char[len_];
	strncpy(msg_, msg, len_);
}

void binary_reader::market_message::write( std::ofstream& out ) const
{
	read_write_impl::write(out, type_);
	read_write_impl::write(out, time_);
	read_write_impl::write(out, len_);
	read_write_impl::write(out, msg_, len_);
}

binary_reader::market_message::~market_message()
{
	delete[] msg_;
}

boost::uint32_t binary_reader::market_message::type() const
{
	return type_;
}

boost::uint32_t binary_reader::market_message::time() const
{
	return time_;
}

const char* const binary_reader::market_message::msg() const
{
	return msg_;
}

size_t binary_reader::market_message::size() const
{
	return sizeof(type_)+sizeof(time_)+sizeof(len_)+len_;
}
