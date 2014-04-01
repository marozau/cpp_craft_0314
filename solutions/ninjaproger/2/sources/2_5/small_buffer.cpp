#include <iostream>
#include <fstream>
#include "market_message.h"
#include <map>


using namespace std;

static const uint32_t kBufferSize = 2048;

typedef map<uint32_t, map<uint32_t, uint32_t> >TypeMap;
typedef map<uint32_t, uint32_t> TimeMap;


int main()
{
    ifstream in_file(BINARY_DIR "/input.txt",ios_base::binary);
    ofstream out_file(BINARY_DIR "/output.txt",ios_base::binary);
    
    try {
        if(!in_file.is_open()||!out_file.is_open())
            throw runtime_error("unable to open file");
    } catch (runtime_error& e) {
        cout << e.what() << endl;
        return 1;
    }
    
    
    
    TypeMap type_map;
    map<uint32_t, uint32_t> bufferUsedBytesMap;
    uint32_t lastSecond = UINT32_MAX;
    
    while (1) {
        binary_reader::market_message msg(in_file);
        
        if(in_file.eof())
            break;
        
        const uint32_t type = msg.type();
        const uint32_t time = msg.time();
        
        if(lastSecond!=time)
        {
            bufferUsedBytesMap.clear();
            lastSecond = time;
        }
        
        const uint32_t msgBytes = msg.msg_len() + sizeof(uint32_t)*3;
        
        if((bufferUsedBytesMap[type] + msgBytes) > kBufferSize)
            continue;
        
        bufferUsedBytesMap[type]+=msgBytes;
        
        ++type_map[type][time];
        
    }
    
    TypeMap::const_iterator type_iter;
    
    for(type_iter = type_map.begin();type_iter != type_map.end(); ++type_iter)
    {
        const uint32_t type = type_iter->first;
        const TimeMap& sec_map = type_iter->second;
        
        uint32_t cnt = 0;
        uint32_t secs = 0;
        
        TimeMap::const_iterator sec_iter;
        
        for(sec_iter = sec_map.begin();sec_iter != sec_map.end(); ++sec_iter)
        {
            cnt += sec_iter->second;
            secs++;
        }
        
        out_file.write( reinterpret_cast< const char * >( &type), sizeof(type));
        const double avg = cnt/static_cast<double>(secs);
        out_file.write( reinterpret_cast<const char * >( &avg), sizeof(avg));
    }
    
}

