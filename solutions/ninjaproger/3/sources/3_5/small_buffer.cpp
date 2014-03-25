#include <market_message.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <pthread.h>
#include <map>

using namespace boost;
using namespace std;

typedef map<uint32_t, map<uint32_t, uint32_t> >TypeMap;
typedef map<uint32_t, uint32_t> TimeMap;

void *process_data(void* arg)
{
    char *in_file_name = (char*)arg;
    char *out_file_name = new char[strlen(in_file_name)];
    char *file_name_end = strchr(in_file_name, '_');
    sprintf(out_file_name, "output_%s",file_name_end + 1);
    
    string in_path_str = string(BINARY_DIR).append("/").append(in_file_name);
    string out_path_str = string(BINARY_DIR).append("/").append(out_file_name);
    ifstream in(in_path_str);
    ofstream out(out_path_str);
    
    delete out_file_name;
    
    if(!in.is_open()||!out.is_open())
        throw runtime_error("unable to open file");
    
    TypeMap type_map;
    
    while (1) {
        binary_reader::market_message msg(in);
        
        if(in.eof())
            break;
        
        if(msg.msg_len() > (2048 - sizeof(uint32_t)*3))
            continue;
        
        const uint32_t type = msg.type();
        const uint32_t time = msg.time();
        TimeMap sec_map = type_map[type];
        sec_map[time]++;
        type_map[type] = sec_map;
    }
    
    in.close();
    
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
        
        out.write( reinterpret_cast< char * >( &type), sizeof(type));
        double avg = cnt/static_cast<double>(secs);
        out.write( reinterpret_cast< char * >( &avg), sizeof(avg));
    }
    out.close();
    
    pthread_exit(NULL);
}


int main()
{
    filesystem::path binary_path(BINARY_DIR);
    
    if(!exists(binary_path))
        runtime_error("Error:Directory does not exists!");
    
    for(filesystem::directory_iterator itr(binary_path); itr != filesystem::directory_iterator(); ++itr)
    {
        const string path_str = itr->path().filename().string();
        if(is_regular_file(itr->path())&&
           path_str.find("input_")!=string::npos)
        {
            cout << "found file:" << itr->path().filename() << std::endl;
            pthread_t threads[1000];
            
            const char *c_file = itr->path().filename().c_str();
            char * arg_file = new char[strlen(c_file)];
            strcpy(arg_file,c_file);
            
            int i = 0;
            int rc = pthread_create(&threads[i++], NULL, process_data, (void*)arg_file);
            if(rc)
            {
                cout << "Error:return from pthread_create() is:%d" << rc;
            }
        }
    }
    
    pthread_exit(NULL);

}

