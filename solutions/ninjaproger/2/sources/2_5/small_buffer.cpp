#include <iostream>
#include <fstream>
#include "market_message.h"
#include <map>


using namespace std;

int main()
{
    ifstream in_file(BINARY_DIR "/input.txt",std::ios_base::binary);
    ofstream out_file(BINARY_DIR "/output.txt",std::ios_base::binary);
    
    if(!in_file.is_open()||!out_file.is_open())
        throw runtime_error("unable to open file");
    
    map<uint32_t, map<uint32_t, uint32_t> > type_map;
    while (1) {
        binary_reader::market_message msg(in_file);
        
        if(in_file.eof())
            break;
        
        if(msg.type() > 100000)
            continue;
        
        uint32_t type = msg.type();
        uint32_t time = msg.time();
        
        
        cout << type << ":" << time << endl;
        
        map<uint32_t, uint32_t> sec_map = type_map[type];
        uint32_t cnt = sec_map[time];
        sec_map[time] = ++cnt;
        type_map[type] = sec_map;
    }
    
    std::map<uint32_t,map<uint32_t, uint32_t> >::iterator type_iter;
    
    for(type_iter = type_map.begin();type_iter != type_map.end(); ++type_iter)
    {
        uint32_t type = type_iter->first;
        map<uint32_t, uint32_t> sec_map = type_iter->second;
        
        uint32_t cnt = 0;
        uint32_t secs = sec_map.size();
        
        std::map<uint32_t,uint32_t>::iterator sec_iter;
        
        for(sec_iter = sec_map.begin();sec_iter != sec_map.end(); ++sec_iter)
            cnt += sec_iter->second;
        
        binary_reader::Uint32Union wrUintUnion;
        wrUintUnion.integerValue = type;
        out_file.write(wrUintUnion.chars, sizeof(uint32_t));
        
        binary_reader::DblUnion wrDblUnion;
        double avg = cnt/(double)secs;
        wrDblUnion.doubleValue = avg;
        out_file.write(wrDblUnion.chars, sizeof(double));
    }
    
}

