#include <market_message.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/ref.hpp>

static const uint32_t kDelta = 2;

using namespace boost;
using namespace std;

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


