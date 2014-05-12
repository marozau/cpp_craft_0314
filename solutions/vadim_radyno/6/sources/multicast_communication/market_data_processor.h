#ifndef _MULTICAST_COMMUNICATION_MARKET_DATA_PROCESSOR_H_
#define _MULTICAST_COMMUNICATION_MARKET_DATA_PROCESSOR_H_

#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "trade_message.h"
#include "thread_safe_queue.h" 
#include "quote_message.h"

namespace multicast_communication
{
    using namespace common;
    static const char* market_data_file = BINARY_DIR "/market_data.dat";

    class market_data_processor : protected virtual boost::noncopyable
    {
	private:
	    boost::mutex mtx_out_;
        public:
            explicit market_data_processor();
            virtual ~market_data_processor(){}
            virtual thread_safe_queue< trade_message_ptr >& trades();
            virtual thread_safe_queue< quote_message_ptr >& quotes();
            void save_trade(const trade_message_ptr m);
            void save_quote(const quote_message_ptr m);

            typedef std::map<char, int> denom_type;
	    typedef std::vector<message_type> types_messages_;
        protected:
            friend class market_data_receiver;
            static denom_type denom_map; 
	    static int get_denominator(const char c); 
	    virtual void new_trade( const  trade_message_ptr message );
	    virtual void new_quote(const  quote_message_ptr message ); 

            thread_safe_queue< trade_message_ptr > trades_;
            thread_safe_queue< quote_message_ptr > quotes_;

	    static void split_block(const message_type & m, types_messages_& v);

            template <typename T>
            static void parse_quote( quote_message_ptr quote_message )
                {
                    if (!quote_message)
		    {
		        return;
		    }

                    if(!is_valid_type<short_quote_message>(quote_message->raw_) && !is_valid_type<long_quote_message>(quote_message->raw_) )
                        throw std::logic_error("Invalid quote type");
                    const message_type& raw = quote_message->raw_;
                    quote_message->category_ = raw[0];
                    quote_message->type_ = raw[1];
                    quote_message->timestamp_ = get_value_from_raw_by_field<T, std::string>(raw, T::TIMESTAMP);
                    quote_message->security_symbol_ = get_value_from_raw_by_field<T, std::string>(raw, T::SECURITY_SYMBOL);                    
                    boost::algorithm::trim(quote_message->security_symbol_);
                    quote_message->bid_price_demoninator_indicator_ =  get_value_from_raw_by_field<T, char>(raw, T::BID_PRICE_DENOMINATOR_INDICATOR);
                    quote_message->bid_price_ = get_value_from_raw_by_field<T, double>(raw, T::BID_PRICE) / get_denominator(quote_message->bid_price_demoninator_indicator_);
                    quote_message->bid_size_ = get_value_from_raw_by_field<T, double>(raw, T::BID_SIZE);
                    quote_message->offer_price_denominator_indicator_ = get_value_from_raw_by_field<T, char>(raw, T::OFFER_PRICE_DENOMINATOR_INDICATOR);
                    quote_message->offer_price_ = get_value_from_raw_by_field<T, double>(raw, T::OFFER_PRICE) / get_denominator(quote_message->offer_price_denominator_indicator_);
                    quote_message->offer_size_ = get_value_from_raw_by_field<T, double>(raw, T::OFFER_SIZE);
                }

            template <typename T>
                static void parse_trade( trade_message_ptr trade_message )
                {
		    if (!trade_message)
		    {
		        return;
		    }
                    if(!is_valid_type<short_trade_message>(trade_message->raw_) && !is_valid_type<long_trade_message>(trade_message->raw_) )
                        throw std::logic_error("Invalid trade type");
                    const message_type& raw = trade_message->raw_;
                    trade_message->category_ = raw[0];
                    trade_message->type_ = raw[1];
                    trade_message->timestamp_ = get_value_from_raw_by_field<T, std::string>(raw, T::TIMESTAMP);
                    trade_message->security_symbol_ = get_value_from_raw_by_field<T, std::string>(raw, T::SECURITY_SYMBOL);
                    boost::algorithm::trim(trade_message->security_symbol_);
                    trade_message->price_denom_code_ = get_value_from_raw_by_field<T, char>(raw, T::PRICE_DENOMINATOR_INDICATOR);
                    trade_message->price_ = get_value_from_raw_by_field<T, double>(raw, T::TRADE_PRICE) / get_denominator(trade_message->price_denom_code_);
                    trade_message->volume_ = get_value_from_raw_by_field<T, double>(raw, T::TRADE_VOLUME);
                }

            template <typename T>
                static bool is_valid_type(const message_type& m)
                {
                    for(size_t i = 0; i < T::RESTRICTION_SIZE; ++i)
                    {
                        if( m[0] == T::RESTRICTION_CATEGORY[i] && m[1] == T::RESTRICTION_TYPE[i] )
                            return true;
                    }
                    return false;
                }

            template <typename T, typename N>
                static N get_value_from_raw_by_field(const message_type & raw, const int field)
                {
                    message_type mess(raw.begin() + T::OFFSET[field], raw.begin() + T::OFFSET[field] + T::LENGTH[field]);
                    return boost::lexical_cast<N>( std::string(mess.begin(), mess.begin() + mess.size()) );
                }
    };

}

#endif // _MULTICAST_COMMUNICATION_MARKET_DATA_PROCESSOR_H_
