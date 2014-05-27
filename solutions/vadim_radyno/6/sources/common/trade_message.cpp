#include <string>
#include "trade_message.h"

namespace common
{
    trade_message::trade_message( const message_type& m ) : raw_( m )
    { }

    const int long_trade_message::LENGTH[long_trade_message::FIELDS] = {
        6,  //Timestamp
        11, //Security Symbol                              
        1,  //Temporary Suffix                             
        1,  //Test Message Indicator                       
        1,  //Trade Reporting Facility Identifier          
        1,  //Primary Listing Market Participant Identifier
        1,  //Reserved                                     
        1,  //Financial Status                             
        3,  //Currency Indicator                           
        1,  //Held Trade Indicator                         
        1,  //Instrument Type                              
        3,  //Seller’s Sale Days                           
        4,  //Sale Condition                               
        1,  //Trade Through Exempt Indicator               
        1,  //Short Sale Restriction Indicator             
        1,  //Reserved                                     
        1,  //Price Denominator Indicator                  
        12, //Trade Price                                  
        9,  //Trade Volume                                 
        1,  //Consolidated High/Low/Last Indicator         
        1,  //Participant Open/High/Low/Last Indicator     
        1,  //Reserved                                     
        1   //Stop Stock Indicator                         
    };

    const int long_trade_message::OFFSET[long_trade_message::FIELDS] = 
    {
        18, //Timestamp
        24, //Security Symbol                              
        35, //Temporary Suffix                             
        36, //Test Message Indicator                       
        37, //Trade Reporting Facility Identifier          
        38, //Primary Listing Market Participant Identifier
        39, //Reserved                                     
        40, //Financial Status                             
        41, //Currency Indicator                           
        44, //Held Trade Indicator                         
        45, //Instrument Type                              
        46, //Seller’s Sale Days                           
        49, //Sale Condition                               
        53, //Trade Through Exempt Indicator               
        54, //Short Sale Restriction Indicator             
        55, //Reserved                                     
        56, //Price Denominator Indicator                  
        57, //Trade Price                                  
        69, //Trade Volume                                 
        78, //Consolidated High/Low/Last Indicator         
        79, //Participant Open/High/Low/Last Indicator     
        80, //Reserved                                     
        81, //Stop Stock Indicator                         
    }; 

    const int short_trade_message::LENGTH[short_trade_message::FIELDS] = 
    {
        6,//Timestamp
        3, //Security Symbol                         
        1, //Sale Condition                          
        4, //Trade Volume                            
        1, //Price Denominator Indicator             
        8, //Trade Price                             
        1, //Consolidated High/Low/Last Indicator    
        1, //Participant Open/High/Low/Last Indicator
        1  //Reserved                                
    };

    const int short_trade_message::OFFSET[short_trade_message::FIELDS] = 
    {
        18, //Timestamp
        24, //Security Symbol                         
        27, //Sale Condition                          
        28, //Trade Volume                            
        32, //Price Denominator Indicator             
        33, //Trade Price                             
        41, //Consolidated High/Low/Last Indicator    
        42, //Participant Open/High/Low/Last Indicator
        43  //Reserved                                
    };

    const char short_trade_message::RESTRICTION_TYPE[short_trade_message::RESTRICTION_SIZE] =
    {
        'I',
        'I'
    };

    const char short_trade_message::RESTRICTION_CATEGORY[short_trade_message::RESTRICTION_SIZE] =
    {
        'E',
        'L'
    };

    const char long_trade_message::RESTRICTION_TYPE[long_trade_message::RESTRICTION_SIZE] =
    {
        'B',
        'B',
        'B'
    };

    const char long_trade_message::RESTRICTION_CATEGORY[long_trade_message::RESTRICTION_SIZE] =
    {
        'B',
        'E',
        'L'
	};    

	ostream& operator<<(ostream& os, const trade_message& mes)
	{       
		os << "[" << mes.category_ << mes.type_ << "," 
			<< mes.security_symbol_ << "," << mes.price_ << "," << mes.volume_ << "]" 
			<< endl;
		return os;
	}
}
