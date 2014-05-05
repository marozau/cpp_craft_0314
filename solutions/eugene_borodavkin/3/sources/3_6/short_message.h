#ifndef _BINARY_DATAFEED_SHORT_MESSAGE_H_
#define _BINARY_DATAFEED_SHORT_MESSAGE_H_

#include <fstream>
#include <cstdint>
#include <cstring>

template <class T>
void readFromBinaryInput(std::ifstream &input, T &t, size_t len = sizeof(T)){
    input.read(reinterpret_cast< char * >( &t ), len);
}

template <class T>
void writeToBinaryOutput( std::ofstream &output, const T &t, size_t len = sizeof(T)){
    output.write(reinterpret_cast< const char* >( &t ), len);
}

class Message{
private:
    char stock_name[8];
    char date_time[8];
    double price;
    double vwap;
    std::uint32_t volume;
    double f1;
    double t1;
    double f2;
    double f3;
    double f4;
public:
    Message(){}
    Message( std::ifstream &in);
    ~Message(){}

    void write( std::ofstream& out );

    char* name();
};

#endif
