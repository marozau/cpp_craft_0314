#include <iostream>
#include <fstream>
#include <boost/thread.hpp>

#include "market_data_processor.h"
#include "trade_message.h"
#include "quote_message.h"

namespace multicast_communication
{
  	market_data_processor::market_data_processor() 
  	{
	boost::mutex::scoped_lock lock( mtx_out_ );
    	std::ofstream os(multicast_communication::market_data_file);
    	os.close();
  	}
	void market_data_processor::new_trade(const trade_message_ptr message)
	{
        if(is_valid_type<short_trade_message>( message->raw_ )) 
            parse_trade<short_trade_message>( message );
        else if(is_valid_type<long_trade_message>( message->raw_ )) 
            parse_trade<long_trade_message>( message ); 
        market_data_processor::save_trade(message); 
        trades_.push( message );
    }

	void market_data_processor::new_quote(const quote_message_ptr message)
	{
        if(is_valid_type<short_quote_message>( message->raw_ ))
            parse_quote<short_quote_message>( message );
        else if(is_valid_type<long_quote_message>( message->raw_ ))
            parse_quote<long_quote_message>( message );
	market_data_processor::save_quote(message);
        quotes_.push( message );
    }

    thread_safe_queue< trade_message_ptr >& market_data_processor::trades()
    { 
        return trades_;
    }
    thread_safe_queue< quote_message_ptr >& market_data_processor::quotes()
    { 
        return quotes_;
    }

    void market_data_processor::save_trade(const trade_message_ptr m)
    { 
	boost::mutex::scoped_lock lock( mtx_out_);
        std::ofstream os(multicast_communication::market_data_file, std::ios::app);
        if (!os.is_open()) 
          throw std::logic_error( "Output file was not opened");
        os << "T " << 
          m->security_symbol_ << " " << 
          m->price_ << " " << 
          m->volume_ << 
          std::endl;
        os.close();
        lock.unlock();
    }
    void market_data_processor::save_quote(const quote_message_ptr m)
    { 
      boost::mutex::scoped_lock lock( mtx_out_ );
        std::ofstream os(multicast_communication::market_data_file, std::ios::app);
		    
        if (!os.is_open()) 
          throw std::logic_error( "Output file was not opened");
        os << "Q " << 
          m->security_symbol_ << " " << 
          m->bid_price_ << " " << 
          m->bid_size_ << " " << 
          m->offer_price_ << " " << 
          m->offer_size_ << 
          std::endl;
        os.close();
        lock.unlock();
    } 

	void market_data_processor::split_block(const message_type & m, types_messages_& v)
	{
        message_type msg;
        for(message_type::const_iterator it = m.begin(); it != m.end(); ++it)
        {
            char c = *it;
            switch(c)
            {
                case 0x01:
                    msg.clear();
                    break;
                case 0x1f:
                    v.push_back(msg);
                    msg.clear();
                    break;
                case 0x03:
                    v.push_back(msg);
                    return;
                default:
                    msg.push_back(c);
            }
        }
    }

    const market_data_processor::denom_type::value_type raw_data[] = { 
        market_data_processor::denom_type::value_type('0', 1),
        market_data_processor::denom_type::value_type('3', 8),
        market_data_processor::denom_type::value_type('4', 16),
        market_data_processor::denom_type::value_type('5', 32),
        market_data_processor::denom_type::value_type('6', 64),
        market_data_processor::denom_type::value_type('7', 128),
        market_data_processor::denom_type::value_type('8', 256),
        market_data_processor::denom_type::value_type('A', 10),
        market_data_processor::denom_type::value_type('B', 100),
        market_data_processor::denom_type::value_type('C', 1000), market_data_processor::denom_type::value_type('D', 10000), market_data_processor::denom_type::value_type('E', 100000),
        market_data_processor::denom_type::value_type('F', 1000000),
        market_data_processor::denom_type::value_type('G', 10000000),
        market_data_processor::denom_type::value_type('H', 100000000),
        market_data_processor::denom_type::value_type('I', 1)
    };

    const long unsigned int num_elems = sizeof raw_data / sizeof raw_data[0];
    market_data_processor::denom_type market_data_processor::denom_map(raw_data, raw_data + num_elems);

	int market_data_processor::get_denominator(const char c)
	{
        denom_type::iterator it = denom_map.find(c);
        if(it == market_data_processor::denom_map.end())
        {
            std::cerr << c << " wrong denominator code." << std::endl;
            throw std::logic_error("wrong denominator code.");
        }
        const int denom = it->second;
        if(denom == 0)
        {
            std::cerr << "Zero denominator." << std::endl;
            throw std::logic_error("Zero denominator");
        }
        return denom;
    }

}
