#include <iostream>
#include <fstream>
#include "stock_data.h"

using namespace std;


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
    
    
    while (1) {
        
        binary_reader::stock_data stk_data(in_file);
        
        if(in_file.eof())
            break;
        
        stk_data.write(out_file);
    }
    
    in_file.close();
    out_file.close();
}

