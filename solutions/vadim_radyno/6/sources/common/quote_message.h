#ifndef _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
using namespace std;

namespace common
{
    typedef vector<char> message_type;

    struct quote_message: virtual private boost::noncopyable
	{ 
		quote_message(const message_type&);

		string security_symbol_;
		char bid_price_demoninator_indicator_;
		double bid_price_;
		double bid_size_;
		char offer_price_denominator_indicator_;
		double offer_price_;
		double offer_size_;
		char category_;
		char type_;
		string timestamp_;
		message_type raw_;

        friend std::ostream& operator<<(ostream&, const quote_message&);
    };

    struct long_quote_message
    {
        static const int FIELDS = 30;
        static const int SIZE = 102;

        static const size_t RESTRICTION_SIZE = 3;
        enum
        {
            TIMESTAMP,
            SECURITY_SYMBOL,
            TEMPORARY_SUFFIX,
            TEST_MESSAGE_INDICATOR,
            PRIMARY_LISTING_MARKET_PARTICIPANT_IDENTIFIER,
            SIP_GENERATED_MESSAGE_IDENTIFIER,
            RESERVED,
            FINANCIAL_STATUS,
            CURRENCY_INDICATOR,
            INSTRUMENT_TYPE,
            CANCEL_CORRECTION_INDICATOR,
            SETTLEMENT_CONDITION,
            MARKET_CONDITION,
            QUOTE_CONDITION,
            LIMIT_UP_LIMIT_DOWN_LULD_INDICATOR,
            RETAIL_INTEREST_INDICATOR,
            BID_PRICE_DENOMINATOR_INDICATOR,
            BID_PRICE,
            BID_SIZE,
            OFFER_PRICE_DENOMINATOR_INDICATOR,
            OFFER_PRICE,
            OFFER_SIZE,
            FINRA_MARKET_MAKER_ID,
            RESERVED_2,
            NATIONAL_BBO_LULD_INDICATOR,
            FINRA_BBO_LULD_INDICATOR,
            SHORT_SALE_RESTRICTION_INDICATOR,
            RESERVED_3,
            NATIONAL_BBO_INDICATOR,
            FINRA_BBO_INDICATOR
        };
        static const int LENGTH[FIELDS];
        static const int OFFSET[FIELDS];

        static const char RESTRICTION_TYPE[RESTRICTION_SIZE];
        static const char RESTRICTION_CATEGORY[RESTRICTION_SIZE];
    };

    struct short_quote_message
    {
        static const int FIELDS = 15;
        static const int SIZE = 58;

        static const size_t RESTRICTION_SIZE = 3;
        enum
        {
            TIMESTAMP,
            SECURITY_SYMBOL,
            QUOTE_CONDITION,
            LIMIT_UP_LIMIT_DOWN_LULD_INDICATOR,
            RESERVED_1,
            BID_PRICE_DENOMINATOR_INDICATOR,
            BID_PRICE,
            BID_SIZE,
            RESERVED_2,
            OFFER_PRICE_DENOMINATOR_INDICATOR,
            OFFER_PRICE,
            OFFER_SIZE,
            RESERVED_3,
            NATIONAL_BBO_INDICATOR,
            FINRA_BBO_INDICATOR,
            TOTAL_LENGTH
        };
        static const int LENGTH[FIELDS];
        static const int OFFSET[FIELDS];

        static const char RESTRICTION_TYPE[RESTRICTION_SIZE];
        static const char RESTRICTION_CATEGORY[RESTRICTION_SIZE];
    };

    typedef boost::shared_ptr< quote_message > quote_message_ptr;
}

#endif // _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
