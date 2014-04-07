#include <market_message.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/ref.hpp>
#include <map>

using namespace boost;
using namespace std;

static const uint32_t kBufferSize = 2048;

typedef map<uint32_t, map<uint32_t, uint32_t> >TypeMap;
typedef map<uint32_t, uint32_t> TimeMap;


void process_data(const filesystem::path & in_fname_path)
{
    filesystem::path out_fname_path(in_fname_path);
    
    string out_fname_str(out_fname_path.filename().string());
    const char * str_to_replace = "input_";
    size_t pos = out_fname_str.find(str_to_replace);
    size_t len = strlen(str_to_replace);
    out_fname_str.replace(pos, len,"output_");
    out_fname_path.remove_filename();
    out_fname_path /= out_fname_str;
    
    std::ifstream in_file(in_fname_path.string(),ios_base::binary);
    std::ofstream out_file(out_fname_path.string(),ios_base::binary);
    
    try {
        if(!in_file.is_open()||!out_file.is_open())
            throw runtime_error("Error:Unable to open file");
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
        return;
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


int main()
{
    filesystem::path binary_path(BINARY_DIR);
    
    try {
        if(!exists(binary_path))
            throw runtime_error("Error:Directory does not exists!");
        
        for(filesystem::directory_iterator itr(binary_path); itr != filesystem::directory_iterator(); ++itr)
        {
            const string path_str = itr->path().filename().string();
            if(is_regular_file(itr->path())&&
               path_str.find("input_")!=string::npos)
            {
                boost::thread thrd(process_data,boost::ref(itr->path()));
                thrd.join();
            }
        }
    } catch (std::exception& e) {
        cerr << e.what() << endl;
    }


}

