#include <market_message.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <pthread.h>

using namespace boost;
using namespace std;

void *process_data(void* arg)
{
    char *in_file = (char*)arg;
    char *out_file = new char[strlen(in_file)];
    char *file_name_end = strchr(in_file, '_');
    sprintf(out_file, "output_%s",file_name_end + 1);
    
    string in_path_str = string(BINARY_DIR).append("/").append(in_file);
    string out_path_str = string(BINARY_DIR).append("/").append(out_file);
    ifstream in(in_path_str);
    ofstream out(out_path_str);
    
    delete out_file;
    
    if(!in.is_open()||!out.is_open())
    {
        runtime_error("Error:Couldn't open file!");
    }
    
    uint32_t max_t = 0;
    
    while (1) {
        
        binary_reader::market_message msg(in);
        
        if(in.eof())
            break;
        
        const uint32_t msg_type = msg.type();
        
        if((msg_type != binary_reader::market_message::MARKET_OPEN&&
            msg_type != binary_reader::market_message::TRADE&&
            msg_type != binary_reader::market_message::QUOTE&&
            msg_type != binary_reader::market_message::MARKET_CLOSE))
            continue;
        
        int64_t timeDelta = static_cast<int64_t>(max_t) - 2;
        
        if(msg.time() > timeDelta)
            msg.write(out);
        
        max_t = max(max_t,msg.time());
    }
    
    in.close();
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
        if(is_regular_file(itr->path()))
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


