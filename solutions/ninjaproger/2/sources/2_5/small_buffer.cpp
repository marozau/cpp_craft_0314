#include <iostream>
#include <fstream>
#include "market_message.h"
#include <map>


using namespace std;
typedef map<uint32_t, map<uint32_t, uint32_t> >TypeMap;
typedef map<uint32_t, uint32_t>TimeMap;

int main()
{
    ifstream in_file(BINARY_DIR "/input.txt",std::ios_base::binary);
    ofstream out_file(BINARY_DIR "/output.txt",std::ios_base::binary);
    
    if(!in_file.is_open()||!out_file.is_open())
        throw runtime_error("unable to open file");
    
    
    TypeMap type_map;
    
    while (1) {
        binary_reader::market_message msg(in_file);
        
        if(in_file.eof())
            break;
        
        const uint32_t type = msg.type();
        const uint32_t time = msg.time();
        TimeMap sec_map = type_map[type];
        sec_map[time]++;
        type_map[type] = sec_map;
    }
    
    TypeMap::iterator type_iter;
    
    for(type_iter = type_map.begin();type_iter != type_map.end(); ++type_iter)
    {
        uint32_t type = type_iter->first;
        TimeMap sec_map = type_iter->second;
        
        uint32_t cnt = 0;
        uint32_t secs = 0;
        
        TimeMap::iterator sec_iter;
        
        for(sec_iter = sec_map.begin();sec_iter != sec_map.end(); ++sec_iter)
        {
            cnt += sec_iter->second;
            secs++;
        }
        
        out_file.write( reinterpret_cast< char * >( &type), sizeof(type));
        double avg = cnt/static_cast<double>(secs);
        out_file.write( reinterpret_cast< char * >( &avg), sizeof(avg));
    }
    
}

