#include <iostream>
#include <fstream>
#include "stock_data.h"


int main()
{
    std::ifstream in_file(BINARY_DIR "/input.txt",std::ios_base::binary);
    std::ofstream out_file(BINARY_DIR "/output.txt",std::ios_base::binary);
    
    if(!in_file.is_open()||!out_file.is_open())
        throw std::runtime_error("unable to open file");
    
    
    while (1) {
        
        binary_reader::stock_data stk_data(in_file);
        
        if(in_file.eof())
            break;
        
        stk_data.write(out_file);
    }
    
    
}

