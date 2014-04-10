#include <iostream>
#include <fstream>
#include "market_message.h"

static const uint32_t kDelta = 2;

using namespace std;

int main()
{
    std::ifstream in_file(BINARY_DIR "/input.txt",ios_base::binary);
    std::ofstream out_file(BINARY_DIR "/output.txt",ios_base::binary);
    
    try {
        if(!in_file.is_open()||!out_file.is_open())
            throw runtime_error("unable to open file");
    } catch (runtime_error& e) {
        cout << e.what() << endl;
        return 1;
    }
    
    uint32_t max_t = 0;
    
    while (1) {

        binary_reader::market_message msg(in_file);
        
        if(in_file.eof())
            break;
        
        const uint32_t msg_type = msg.type();
        
        if((msg_type != binary_reader::market_message::MARKET_OPEN&&
            msg_type != binary_reader::market_message::TRADE&&
            msg_type != binary_reader::market_message::QUOTE&&
            msg_type != binary_reader::market_message::MARKET_CLOSE))
            continue;
        
        const int64_t timeDelta = static_cast<int64_t>(max_t) - kDelta;
        
        if(msg.time() > timeDelta)
            msg.write(out_file);
        
        max_t = max(max_t,msg.time());
    }

    in_file.close();
    out_file.close();
}

