#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include <string>
#include <algorithm>
#include <set>
#include <sstream>
#include <iomanip>
#include <cmath>


int main(int argc, char **argv) {
    std::ifstream input;
    std::ofstream output;

    input.open(BINARY_DIR "/input.txt");
    output.open(BINARY_DIR "/output.txt");
    if (not input.is_open()) {
        std::cerr << "Unable to open the input file. Reason: " << 
                      strerror(errno) << "\n";
        return 1;
    }
    if (not output.is_open()) {
        std::cerr << "Unable to open the output file. Reason: " << 
                      strerror(errno) << "\n";
        return 1;
    }

    unsigned int N;
    std::set<std::string> codes;
    std::string line;

    std::getline(input, line);
    std::istringstream(line) >> N;
    //piece of useful debug print
    //std::cerr << "DEBUG: N is " << N << "\n";
    
    unsigned int line_count = 0;
    double next_value = 0.0;
    std::string next_str_value;
    std::set<std::string>::iterator it;

    while ( std::getline(input, line) ) {
        next_value = ::strtod(line.c_str(), 0);
        std::ostringstream ss;
        ss  << std::fixed << std::setprecision(5) << ::trunc(next_value * 10000) / 10000;
        next_str_value = ss.str();

        //piece of useful debug print
        //std::cerr << "DEBUG: next_str_value is " << next_str_value << "\n";
        //std::cerr << "DEBUG: line_count is " << line_count << "\n";
        if (line_count < N) {
            codes.insert(next_str_value);
            ++line_count;
            continue;
        }
        it = codes.find(next_str_value);
        if (it == codes.end()) {
            output << "NO" << "\n";
        } else {
            output << "YES" << "\n";
        }
        
        ++line_count;
    }

    input.close();
    output.close();


    return 0;
}
