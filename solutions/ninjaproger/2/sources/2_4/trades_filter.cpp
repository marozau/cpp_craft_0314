#include <iostream>
#include <fstream>
#include "market_message.h"

int main()
{
    std::ifstream in_file(BINARY_DIR "/input.txt",std::ios_base::binary);
    std::ofstream out_file(BINARY_DIR "/output.txt",std::ios_base::binary);
    
    if(!in_file.is_open()||!out_file.is_open())
        throw std::runtime_error("unable to open file");
    
    uint32_t max_t = 0;
    
    while (1) {

        binary_reader::market_message msg(in_file);
        
        if(in_file.eof())
            break;
        
        uint32_t msg_type = msg.type();
        
        if((msg_type != binary_reader::market_message::MARKET_OPEN&&
            msg_type != binary_reader::market_message::TRADE&&
            msg_type != binary_reader::market_message::QUOTE&&
            msg_type != binary_reader::market_message::MARKET_CLOSE))
            continue;
        
        int64_t timeDelta = (int64_t)max_t - 2;
        
        if(msg.time() > timeDelta)
            msg.write(out_file);
        
        max_t = std::max(max_t,msg.time());
    }

    in_file.close();
    out_file.close();
}

