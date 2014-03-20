#include "market_message.h"
#include <cstring>



binary_reader::market_message::market_message( std::ifstream& _in )
    : m_type(readValue<boost::uint32_t>(_in))
    , m_time(readValue<boost::uint32_t>(_in))
    , m_len(readValue<boost::uint32_t>(_in))
{
    m_msg.resize(m_len + 1);
    _in.read(&m_msg[0], m_len);
    m_msg[m_msg.size() - 1] = '\0';
}


binary_reader::market_message::market_message( const boost::uint32_t _type, const boost::uint32_t _time, const char* const _msg )
    : m_type(_type)
    , m_time(_time)
    , m_len(static_cast<boost::uint32_t>(strlen(_msg)))
{
    m_msg.resize(m_len + 1);
    memmove(&m_msg[0], _msg, m_len);
    m_msg[m_msg.size() - 1] = '\0';
}


void binary_reader::market_message::write( std::ofstream& out )
{
    out.write(reinterpret_cast<char*>(&m_type), sizeof(m_type));
    out.write(reinterpret_cast<char*>(&m_time), sizeof(m_time));
    out.write(reinterpret_cast<char*>(&m_len), sizeof(m_len));
    out.write(&m_msg[0], m_len);
}


binary_reader::market_message::~market_message()
{
}


boost::uint32_t binary_reader::market_message::type() const
{
    return m_type;
}


boost::uint32_t binary_reader::market_message::time() const
{
    return m_time;
}


const char* const binary_reader::market_message::msg() const
{
    if (m_msg.empty())
    {
        return nullptr;
    }

    return &m_msg[0];
}


bool binary_reader::market_message::isValidType() const
{
    if (    static_cast<boost::uint32_t>(eMarketType::BEGIN) <= type()
        &&  static_cast<boost::uint32_t>(eMarketType::END)   >= type())
    {
        return true;
    }
    return false;
}


bool binary_reader::market_message::isValidTime( const boost::uint32_t _max_time )
{
    return time() + 2 > _max_time;
}
