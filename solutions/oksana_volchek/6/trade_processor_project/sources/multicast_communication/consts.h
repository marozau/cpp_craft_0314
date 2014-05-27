#ifndef _MULTICAST_COMMUNICATION_CONSTS_H_
#define _MULTICAST_COMMUNICATION_CONSTS_H_

#include <string>
#include <map>
#include <set>
#include "boost/assign.hpp"
#include <boost/date_time/posix_time/ptime.hpp>

namespace consts {

	namespace file_path {
		const std::string config_path = "/config.ini";
		const std::string output_path = "/market_data.dat";
	}
	
	namespace separator {
		const char start_block = 0x01;
		const char start_inner_block = 0x1F;
		const char end_block = 0x03;
	}
	
	namespace types {
		const std::set<char> tr_correct_type = boost::assign::list_of('B') ('I');
		const std::set<char> tr_correct_category = boost::assign::list_of('E') ('L');

		const std::set<char> qt_correct_category = boost::assign::list_of('E') ('L');
		const std::map<char, char> qt_correct_type = boost::assign::map_list_of('B', 'l') ('D', 's');
	}

	namespace convert_data {
		const std::map<char, boost::uint32_t> time_stamp = boost::assign::map_list_of('0', 0) ('1', 1) ('2', 2) ('3', 3) ('4', 4) ('5', 5)
			('6', 6) ('7', 7) ('8', 8) ('9', 9) (':', 10) (';', 11) ('<', 12) ('=', 13) ('>', 14) ('?', 15) 
			('@', 16) ('A', 17) ('B', 18) ('C', 19) ('D', 20) ('E', 21) ('F', 22) ('G', 23) ('H', 24) ('I', 25)
			('J', 26) ('K', 27) ('L', 28) ('M', 29) ('N', 30) ('O', 31) ('P', 32) ('Q', 33) ('R', 34) ('S', 35)
			('T', 36) ('U', 37) ('V', 38) ('W', 39) ('X', 40) ('Y', 41) ('Z', 42) ('[', 43) ('\\', 44) (']', 45)
			('^', 46) ('_', 47) ('`', 48) ('a', 49) ('b', 50) ('c', 51) ('d', 52) ('e', 53) ('f', 54) ('g', 55)
			('h', 56) ('i', 57) ('j', 58) ('k', 59);

		const std::map<char, size_t> denominators = boost::assign::map_list_of('0', 0) ('3', 8) ('4', 16) ('5', 32) ('6', 64) ('7', 128) ('8', 256)
			('A', 10) ('B', 100) ('C', 1000) ('D', 10000) ('E', 100000) ('F', 1000000) ('G', 10000000) ('H', 100000000) ('I', 1);

		const boost::posix_time::ptime initial_moment(boost::gregorian::date(1900, 1, 1));
		//const boost::uint32_t seccount = initial_moment;
	}

	namespace tr_field_length {
		const size_t header_length = 24;
		const size_t time_length = 6;

		const size_t short_msg_length = 44;
		const size_t short_sec_symbol_length = 3;
		const size_t short_volume_length = 4;
		const size_t short_price_length = 8;
		
		const size_t long_msg_length = 82;
		const size_t long_sec_symbol_length = 11;
		const size_t long_volume_length = 9;
		const size_t long_price_length = 12;
	}

	namespace tr_start_field {
		const size_t start_time = 18;
		const size_t start_sec_symbol = 24;
		
		const size_t start_short_volume = 28;
		const size_t start_short_denominator = 32;
		const size_t start_short_price = 33;
	
		const size_t start_long_denominator = 56;
		const size_t start_long_price =   57;
		const size_t start_long_volume = 69;
	}

	namespace qt_field_length {
		const size_t header_length = 24;
		const size_t time_length = 6;

		const size_t short_msg_length = 58;
		const size_t short_sec_symbol_length = 3;
		const size_t short_bid_volume_length = 3;
		const size_t short_bid_price_length = 8;
		const size_t short_offer_volume_length = 3;
		const size_t short_offer_price_length = 8;

		const size_t long_msg_length = 102;
		const size_t long_sec_symbol_length = 11;
		const size_t long_bid_volume_length = 7;
		const size_t long_bid_price_length = 12;
		const size_t long_offer_volume_length = 7;
		const size_t long_offer_price_length = 12;
	}

	namespace qt_start_field {
		const size_t start_time = 18;
		const size_t start_sec_symbol = 24;
		
		const size_t start_short_bid_denominator = 30;
		const size_t start_short_bid_price = 31;
		const size_t start_short_bid_volume = 39;
		const size_t start_short_offer_denominator = 43;
		const size_t start_short_offer_price = 44;
		const size_t start_short_offer_volume = 52;

		const size_t start_long_bid_denominator = 51;
		const size_t start_long_bid_price = 52;
		const size_t start_long_bid_volume = 64;
		const size_t start_long_offer_denominator = 71;
		const size_t start_long_offer_price = 72;
		const size_t start_long_offer_volume = 84;
	}
} 

#endif // _MULTICAST_COMMUNICATION_CONSTS_H_
