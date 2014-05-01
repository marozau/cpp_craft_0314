#include "short_message.h"


Message::Message( std::ifstream &in){
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

void Message::write( std::ofstream& out )
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

char* Message::name() {
    return stock_name;
}
