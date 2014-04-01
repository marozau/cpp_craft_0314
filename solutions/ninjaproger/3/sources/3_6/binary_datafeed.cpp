#include "ext_stock_data.h"
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/ref.hpp>


using namespace boost;
using namespace std;


void process_data(const ext_stock_data& stk_data)
{
    filesystem::path out_fname_path(BINARY_DIR);
    out_fname_path /= std::string("output_").append(stk_data.stock_name()).append(".txt");
    std::ofstream out_file(out_fname_path.string(),ios_base::binary|ios_base::app);
    
    try {
        if(!out_file.is_open())
            throw runtime_error("Error:Unable to open file");
        
        stk_data.write(out_file);
        
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
        return;
    }
}



int main()
{
    ifstream in_file(BINARY_DIR "/input.txt",ios_base::binary);
    
    try {
        if(!in_file.is_open())
            throw runtime_error("Error:Unable to open file");
    
        while (1) {
            
            ext_stock_data stk_data(in_file);
            
            if(in_file.eof())
                break;
            
            boost::thread thrd(process_data,boost::ref(stk_data));
            thrd.join();
        }
        
        in_file.close();
        
    } catch (std::exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}

