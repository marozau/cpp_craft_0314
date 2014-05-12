#include <vector>
#include <fstream>

#include <boost/thread.hpp>

#include "test_registrator.h"
#include "market_data_receiver.h"
#include "market_data_processor.h"
#include "udp_listener.h"

namespace multicast_communication
{
    namespace tests_
    { 
        void market_data_receiver_tests()
        {
            {
                market_data_processor processor;
                std::vector<std::pair<std::string, unsigned short> > trades;
                std::vector<std::pair<std::string, unsigned short> > quotes;
                BOOST_CHECK_NO_THROW(market_data_receiver receiver( 1, 1, trades, quotes, processor ));
            }

            {
                std::vector<std::pair<std::string, unsigned short> > t_addr;
                std::vector<std::pair<std::string, unsigned short> > q_addr;

                q_addr.push_back( std::make_pair("233.200.79.0", 61000) );
                q_addr.push_back( std::make_pair("233.200.79.1", 61001) );
                q_addr.push_back( std::make_pair("233.200.79.2", 61002) );
                q_addr.push_back( std::make_pair("233.200.79.3", 61003) );
                q_addr.push_back( std::make_pair("233.200.79.4", 61004) );
                q_addr.push_back( std::make_pair("233.200.79.5", 61005) );
                q_addr.push_back( std::make_pair("233.200.79.6", 61006) );
                q_addr.push_back( std::make_pair("233.200.79.7", 61007) );
                t_addr.push_back( std::make_pair("233.200.79.128", 62128) );
                t_addr.push_back( std::make_pair("233.200.79.129", 62129) );
                t_addr.push_back( std::make_pair("233.200.79.130", 62130) );
                t_addr.push_back( std::make_pair("233.200.79.131", 62131) );
                t_addr.push_back( std::make_pair("233.200.79.132", 62132) );
                t_addr.push_back( std::make_pair("233.200.79.133", 62133) );
                t_addr.push_back( std::make_pair("233.200.79.134", 62134) );
                t_addr.push_back( std::make_pair("233.200.79.135", 62135) );

		market_data_processor processor;
                BOOST_CHECK_NO_THROW(
					market_data_receiver receiver(2, 2, t_addr, q_addr, processor ); 
					receiver.start(); 
					receiver.stop();
					); 
            }
        }
    }
} 
