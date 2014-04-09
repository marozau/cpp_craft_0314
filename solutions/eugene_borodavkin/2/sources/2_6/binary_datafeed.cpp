#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <list>



template <class T>
void readFromBinaryInput(std::ifstream &input, const T &t, size_t len = sizeof(T)){
    input.read((char*)&t, len);
}

template <class T>
void writeToBinaryOutput( std::ofstream &output, const T &t, size_t len = sizeof(T)){
    output.write((char*)&t,len);
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
    Message(std::ifstream &in){
        readFromBinaryInput(in, stock_name);
        readFromBinaryInput(in, date_time);
        readFromBinaryInput(in, price);
        readFromBinaryInput(in, vwap);
        readFromBinaryInput(in, volume);
        readFromBinaryInput(in, f1);
        readFromBinaryInput(in, t1);
        readFromBinaryInput(in, f2);
        readFromBinaryInput(in, f3);
        readFromBinaryInput(in, f4);
    }
    ~Message(){
    }

    void write( std::ofstream& out ) const
    {
        std::uint32_t date = 0;
        int year,day,month;
        std::sscanf( date_time, "%4d%2d%2d", &year, &month, &day );
        date = ( year - 1 ) * 372 +  ( month  - 1 )* 31 + day;

        char stock[9];
        memcpy( stock, stock_name, sizeof( stock_name ) );
        writeToBinaryOutput( out, stock );
        writeToBinaryOutput( out, date );
        writeToBinaryOutput( out, vwap );
        writeToBinaryOutput( out, volume );
        writeToBinaryOutput( out, f2 );
    }

};

int main()
{
    std::ifstream input(BINARY_DIR"/input.txt", std::ios::binary);
    std::ofstream output(BINARY_DIR"/output.txt", std::ios::binary);
    while(!input.eof()){
        Message msg(input);
        msg.write(output);
    }

    return 0;
}

