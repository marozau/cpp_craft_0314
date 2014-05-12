#include <vector>
#include <string>

#include "test_registrator.h"

#include "market_data_processor.h"
#include "trade_message.h"
#include "quote_message.h"

#include <boost/make_shared.hpp>

namespace multicast_communication
{
    namespace tests_
    { 
        using namespace common;

        static message_type message(std::string const& s)
        {
            return message_type(s.begin(), s.end());
        }

        static trade_message_ptr t_m(std::string const& s)
        {
            trade_message_ptr t = boost::make_shared<trade_message>(message(s));
            return t;
        }
        static quote_message_ptr q_m(std::string const& s)
        {
            quote_message_ptr q = boost::make_shared<quote_message>(message(s));
            return q;
        }

        struct market_data_processor_helper: public market_data_processor
        {

            static void test_parse_short_quote()
            {
                quote_message_ptr p = q_m("EDEO A  003759032T:J_073ADMR  B00004147006 B00004148004 12"); 
                market_data_processor::parse_quote<short_quote_message>(p);
                BOOST_CHECK_EQUAL("ADM", p->security_symbol_);
                BOOST_CHECK_EQUAL(41.47, p->bid_price_);
                BOOST_CHECK_EQUAL(6, p->bid_size_);
                BOOST_CHECK_EQUAL(41.48, p->offer_price_);
                BOOST_CHECK_EQUAL(4, p->offer_size_);
                BOOST_CHECK_EQUAL('E', p->category_);
                BOOST_CHECK_EQUAL('D', p->type_);
                BOOST_CHECK_EQUAL(":J_073", p->timestamp_);
            }
            static void test_parse_long_quote()
            {
                quote_message_ptr p = q_m("EBEO A  003759035N:J_077ALU             0    AAAR CD0000000423000000147D0000000424000000380     A   02"); 
                market_data_processor::parse_quote<long_quote_message>(p);
                BOOST_CHECK_EQUAL("ALU", p->security_symbol_);
                BOOST_CHECK_EQUAL(4.23, p->bid_price_);
                BOOST_CHECK_EQUAL(147, p->bid_size_);
                BOOST_CHECK_EQUAL(4.24, p->offer_price_);
                BOOST_CHECK_EQUAL(380, p->offer_size_);
                BOOST_CHECK_EQUAL('E', p->category_);
                BOOST_CHECK_EQUAL('B', p->type_);
                BOOST_CHECK_EQUAL(":J_077", p->timestamp_);
            }
            static void test_parse_short_trade()
            {
                trade_message_ptr p = t_m("EIAO A  000146235T:3]008ACN@0100B00007790DD "); 
                market_data_processor::parse_trade<short_trade_message>(p);
                BOOST_CHECK_EQUAL('E', p->category_);
                BOOST_CHECK_EQUAL('I', p->type_);
                BOOST_CHECK_EQUAL("ACN", p->security_symbol_);
                BOOST_CHECK_EQUAL(77.9, p->price_);
                BOOST_CHECK_EQUAL(100, p->volume_);
            }
            static void test_parse_long_trade()
            { 
                trade_message_ptr p = t_m("EBAO A  000146234N:3]004ACN             0     000 F  1  D000000779000000000100DD 0"); 
                market_data_processor::parse_trade<long_trade_message>(p);
                BOOST_CHECK_EQUAL("ACN", p->security_symbol_);
                BOOST_CHECK_EQUAL('E', p->category_);
                BOOST_CHECK_EQUAL('B', p->type_);
                BOOST_CHECK_EQUAL(77.9, p->price_);
                BOOST_CHECK_EQUAL(100, p->volume_);
            }
            static void test_split_block()
            {
                std::vector<message_type> dest;
                std::string m1("message1");
                std::string m2("message1");
                std::string m3("message1");
                std::string m4("message1");
                std::string s("\x01"+m1+"\x1f"+m2+"\x1f"+m3+"\x03\x01"+m4+"\x03");
                std::vector<char> source(s.begin(), s.end());
                market_data_processor::split_block(source, dest);
                BOOST_CHECK_EQUAL(3, dest.size());
            } 
            static void test_is_valid_type()
            {
                BOOST_CHECK_EQUAL(true, market_data_processor::is_valid_type<short_trade_message>(
                            message("EIAO A  000146235T:3]008ACN@0100B00007790DD")));
                BOOST_CHECK_EQUAL(true, market_data_processor::is_valid_type<short_trade_message>(
                            message("LIAO A  000146235T:3]008ACN@0100B00007790DD"))); 


                BOOST_CHECK_EQUAL(true, market_data_processor::is_valid_type<long_trade_message>(
                            message("BBAO A  000146235T:3]008ACN@0100B00007790DD")));
                BOOST_CHECK_EQUAL(true, market_data_processor::is_valid_type<long_trade_message>(
                            message("EBAO A  000146235T:3]008ACN@0100B00007790DD")));
                BOOST_CHECK_EQUAL(true, market_data_processor::is_valid_type<long_trade_message>(
                            message("LBAO A  000146235T:3]008ACN@0100B00007790DD")));

                BOOST_CHECK_EQUAL(true, market_data_processor::is_valid_type<short_quote_message>(
                            message("EDAO A  000146235T:3]008ACN@0100B00007790DD")));
                BOOST_CHECK_EQUAL(true, market_data_processor::is_valid_type<short_quote_message>(
                            message("LDAO A  000146235T:3]008ACN@0100B00007790DD"))); 

                BOOST_CHECK_EQUAL(true, market_data_processor::is_valid_type<long_quote_message>(
                            message("BBAO A  000146235T:3]008ACN@0100B00007790DD")));
                BOOST_CHECK_EQUAL(true, market_data_processor::is_valid_type<long_quote_message>(
                            message("EBAO A  000146235T:3]008ACN@0100B00007790DD")));
                BOOST_CHECK_EQUAL(true, market_data_processor::is_valid_type<long_quote_message>(
                            message("LBAO A  000146235T:3]008ACN@0100B00007790DD")));
            }

        };

        void market_data_processor_tests()
        {
            market_data_processor_helper::test_parse_short_quote();
            market_data_processor_helper::test_parse_long_quote();
            market_data_processor_helper::test_parse_short_trade();
            market_data_processor_helper::test_parse_long_trade();
            market_data_processor_helper::test_split_block();
            market_data_processor_helper::test_is_valid_type();
        }
    }
}
