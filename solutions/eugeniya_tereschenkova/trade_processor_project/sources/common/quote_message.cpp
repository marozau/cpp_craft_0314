#include <string>
#include <iostream>

#include "quote_message.h"

namespace common
{
    quote_message::quote_message(const message_type& m) : raw_(m)
    { } 

    const int long_quote_message::LENGTH[long_quote_message::FIELDS] = {
        6,// Timestamp
        11,// Security Symbol
        1, // Temporary Suffix
        1, // Test Message Indicator
        1, // Primary Listing Market Participant Identifier
        1, // SIP Generated Message Identifier
        1, // Reserved
        1, // Financial Status
        3, // Currency Indicator
        1, // Instrument Type
        1, // Cancel/Correction Indicator
        1, // Settlement Condition
        1, // Market Condition
        1, // Quote Condition
        1, // Limit Up-Limit Down (LULD) Indicator
        1, // Retail Interest Indicator
        1, // Bid Price / Lower Limit Price Band Denominator Indicator
        12,// Bid Price / Lower Limit Price Band
        7, // Bid Size in Units of Trade
        1, // Offer Price / Upper Limit Price Band Denominator Indicator
        12,// Offer Price / Upper Limit Price Band
        7, // Offer Size in Units of Trade
        4, // FINRA Market Maker ID
        1, // Reserved
        1, // National BBO LULD Indicator
        1, // FINRA BBO LULD Indicator
        1, // Short Sale Restriction Indicator
        1, // Reserved
        1, // National BBO Indicator
        1  // FINRA BBO Indicator
    };     // Total Length 102
    const int long_quote_message::OFFSET[long_quote_message::FIELDS] =
    {
        18, // Timestamp
        24, // Security Symbol
        35, // Temporary Suffix
        36, // Test Message Indicator
        37, // Primary Listing Market Participant Identifier
        38, // SIP Generated Message Identifier
        39, // Reserved
        40, // Financial Status
        41, // Currency Indicator
        44, // Instrument Type
        45, // Cancel/Correction Indicator
        46, // Settlement Condition
        47, // Market Condition
        48, // Quote Condition
        49, // Limit Up-Limit Down (LULD) Indicator
        50, // Retail Interest Indicator
        51, // Bid Price / Lower Limit Price Band Denominator Indicator
        52, // Bid Price / Lower Limit Price Band
        64, // Bid Size in Units of Trade
        71, // Offer Price / Upper Limit Price Band Denominator Indicator
        72, // Offer Price / Upper Limit Price Band
        84, // Offer Size in Units of Trade
        91, // FINRA Market Maker ID
        95, // Reserved
        96, // National BBO LULD Indicator
        97, // FINRA BBO LULD Indicator
        98, // Short Sale Restriction Indicator
        99, // Reserved
        100,// National BBO Indicator
        101 // FINRA BBO Indicator
    };      // Total Length 102

    const int short_quote_message::LENGTH[short_quote_message::FIELDS] =
    {
        6, //Message Header
        3,  //Security Symbol
        1,  //Quote Condition
        1,  //Limit Up Limit Down (LULD) Indicator
        1,  //Reserved
        1,  //Bid Price Denominator Indicator
        8,  //Bid Short Price
        3,  //Bid Size Units of Trade
        1,  //Reserved
        1,  //Offer Price Denominator Indicator
        8,  //Offer Short Price
        3,  //Offer Size in Units of Trade
        1,  //Reserved
        1,  //National BBO Indicator
        1   //FINRA BBO Indicator
    };

    const int short_quote_message::OFFSET[short_quote_message::FIELDS] =
    {
        18,  //Message Header
        24, //Security Symbol
        27, //Quote Condition
        28, //Limit Up Limit Down (LULD) Indicator
        29, //Reserved
        30, //Bid Price Denominator Indicator
        31, //Bid Short Price
        39, //Bid Size Units of Trade
        42, //Reserved
        43, //Offer Price Denominator Indicator
        44, //Offer Short Price
        52, //Offer Size in Units of Trade
        55, //Reserved
        56, //National BBO Indicator
        57  //FINRA BBO Indicator
    };

    const char short_quote_message::RESTRICTION_TYPE[short_quote_message::RESTRICTION_SIZE] =
    {
        'D',
        'D'
    };

    const char short_quote_message::RESTRICTION_CATEGORY[short_quote_message::RESTRICTION_SIZE] =
    {
        'E',
        'L'
    };

    const char long_quote_message::RESTRICTION_TYPE[long_quote_message::RESTRICTION_SIZE] =
    {
        'B',
        'B',
        'B'
    };

    const char long_quote_message::RESTRICTION_CATEGORY[long_quote_message::RESTRICTION_SIZE] =
    {
        'B',
        'E',
        'L'
    }; 

    ostream& operator<<(ostream& os, const quote_message& mes)
    {
        os << mes.category_ << mes.type_ << endl;
        os << mes.security_symbol_ << endl;
        os << mes.bid_price_ << endl;
        os << mes.bid_size_ << endl;;
        os << mes.offer_price_ << endl;
        os << mes.offer_size_  << endl;
        os << endl;
        return os;
    }
}
