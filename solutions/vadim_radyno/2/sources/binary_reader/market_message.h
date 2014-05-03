#ifndef _BINARY_READER_MARKET_MESSAGE_H_
#define _BINARY_READER_MARKET_MESSAGE_H_

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>
#include <vector>

namespace binary_reader
{
    class market_message : virtual protected boost::noncopyable
    {
        enum class  eMarketType 
        {
            BEGIN = 1u,
            MARKET_OPEN = BEGIN,
            TRADE,
            QUOTE,
            MARKET_CLOSE,
            END = MARKET_CLOSE
        };

        boost::uint32_t   m_type;
        boost::uint32_t   m_time;
        boost::uint32_t   m_len;
        char* m_msg;

    public:
        explicit market_message( std::ifstream& _in );
        explicit market_message( const boost::uint32_t _type, const boost::uint32_t _time, const char* const _msg );
        void write( std::ofstream& out );
        ~market_message();

        boost::uint32_t type() const;
        boost::uint32_t time() const;
        const char* const msg() const;
        boost::uint32_t size() const 
        {
            return sizeof(m_type) + sizeof(m_time) + sizeof(m_len) + m_len;
        }

        bool isValidType() const;

    private:
        template<typename T> T readValue(std::ifstream& _in)
        {
            T result = 0;
            _in.read(reinterpret_cast<char*>(&result), sizeof(T));

            return result;
        }
    };
}

#endif // _BINARY_READER_MARKET_MESSAGE_H_
