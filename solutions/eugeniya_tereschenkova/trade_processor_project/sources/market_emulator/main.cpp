#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "market_data_receiver.h"
#include "market_data_processor.h"
#include "minute_calculator.h"
#include "udp_listener.h"

using namespace multicast_communication;
using namespace common;

static void service_run(boost::asio::io_service& service)
{
    service.run();
}

static void read_from(std::string const& file, std::vector<message_type>& messages)
{
    message_type m; std::ifstream in(file.c_str(), std::ios::in | std::ios::binary );
    while(in.good())
    {
        char c = static_cast<char>(in.get());
        if(c == 0x01)
        {
            m.clear();
        }
        m.push_back(c);
        if(c == 0x03)
        {
            messages.push_back(m);
        }
    }
}

static unsigned int send_to(boost::asio::io_service& service, 
        std::string const& address, 
        unsigned short port, 
        std::vector<message_type> const& messages)
{
    boost::asio::ip::udp::endpoint endpoint( boost::asio::ip::address::from_string( address ), port );
    boost::asio::ip::udp::socket socket( service, endpoint.protocol() );
    unsigned int send_count = 0u;
    for(std::vector<message_type>::const_iterator it = messages.begin(); 
            it != messages.end(); ++it)
    {
        message_type message = *it;
        socket.send_to( boost::asio::buffer( message ), endpoint );
        ++send_count;
    }
    return send_count;
}

static unsigned int read_and_send(boost::asio::io_service& service,
        std::vector<std::pair<std::string, unsigned short> >& ports) 
{
    unsigned int sent_total = 0u;
	static const char* path = BINARY_DIR "/tests/data/";

    for(std::vector<std::pair<std::string, unsigned short> >::iterator it = ports.begin();
            it != ports.end(); ++it)
    {
        std::vector<message_type> messages;
        read_from(path + it->first + ".udp", messages);
        sent_total += send_to(service, it->first, it->second, messages);
    }
    return sent_total;
} 

int main()
{ 

    boost::asio::io_service service;

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
    market_data_receiver receiver(2, 2, t_addr, q_addr, processor );

    boost::thread run(service_run, boost::ref( service ) );

    receiver.start();

    unsigned int quotes_sent = read_and_send(service, q_addr);
    unsigned int trades_sent = read_and_send(service, t_addr); 

    run.join();
    std::cout << quotes_sent << " quote messages sent" << std::endl;
    std::cout << trades_sent << " trade messages sent" << std::endl;
}
