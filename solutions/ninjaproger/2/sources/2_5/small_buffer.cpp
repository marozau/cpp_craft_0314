#include <iostream>
#include <fstream>
#include "market_message.h"
#include <map>

int main()
{
    std::ifstream in_file(BINARY_DIR "/input.txt",std::ios_base::binary);
    std::ofstream out_file(BINARY_DIR "/output.txt",std::ios_base::binary);
    
    if(!in_file.is_open()||!out_file.is_open())
        throw std::runtime_error("unable to open file");
    
    std::map<uint32_t, uint32_t> msg_map;
    std::map<uint32_t, uint32_t>::iterator iter;
    
    while (1) {
        binary_reader::market_message msg(in_file);
        
        if(in_file.eof())
            break;
        
        if(msg.type() > 100000)
            continue;
        
        uint32_t type = msg.type();
        uint32_t cnt = msg_map[type];
        msg_map[type] = ++cnt;
    }
    
    for(iter = msg_map.begin();iter != msg_map.end(); ++iter)
    {
        binary_reader::Uint32Union wrUnion;
        wrUnion.integer = iter->first;
        out_file.write(wrUnion.chars, sizeof(uint32_t));
        wrUnion.integer = iter->second;
        out_file.write(wrUnion.chars, sizeof(uint32_t));
    }
    
}

