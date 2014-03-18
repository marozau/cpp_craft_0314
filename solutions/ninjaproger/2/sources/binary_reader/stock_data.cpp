#include "stock_data.h"

typedef union
{
    char chars[sizeof(double)];
    double doubleValue;
}DblUnion;

typedef union
{
    char chars[sizeof(uint32_t)];
    uint32_t integerValue;
}UintUnion;


binary_reader::stock_data::stock_data( std::ifstream& in )
{
    DblUnion dblRead;
    UintUnion uintRead;
    
	in.read(_stock_name,sizeof(_stock_name));
    in.read(_date_time, sizeof(_date_time));
    
    in.read(dblRead.chars, sizeof(double));
    _price = dblRead.doubleValue;
    
    in.read(dblRead.chars, sizeof(double));
    _vwap = dblRead.doubleValue;
    
    in.read(uintRead.chars, sizeof(uint32_t));
    _volume = uintRead.integerValue;
    
    in.read(dblRead.chars, sizeof(double));
    _f1 = dblRead.doubleValue;
    
    in.read(dblRead.chars, sizeof(double));
    _t1 = dblRead.doubleValue;
    
    in.read(dblRead.chars, sizeof(double));
    _f2 = dblRead.doubleValue;
    
    in.read(dblRead.chars, sizeof(double));
    _f3 = dblRead.doubleValue;
    
    in.read(dblRead.chars, sizeof(double));
    _f4 = dblRead.doubleValue;
}


binary_reader::stock_data::stock_data( const char* stock_name,
							const char* date_time,
							const double price,
							const double vwap,
							const boost::uint32_t volume,
							const double f1,
							const double t1,
							const double f2,
							const double f3,
							const double f4 )
{
	memcpy(_stock_name,stock_name,sizeof(_stock_name));
    memcpy(_date_time,date_time,sizeof(_date_time));
    _price = price;
    _vwap = vwap;
    _volume = volume;
    _f1 = f1;
    _t1 = t1;
    _f2 = f2;
    _f3 = f3;
    _f4 = f4;
}
binary_reader::stock_data::~stock_data()
{

}
void binary_reader::stock_data::write( std::ofstream& out )
{
    DblUnion dblWrite;
    UintUnion uintWrite;
    
	out.write(_stock_name, sizeof(_stock_name));
    
    char yearChars[5];
    memcpy(yearChars, _date_time, 4);
    yearChars[4] = 0;
    uint32_t years = atoi(yearChars) - 1;
    
    char monthChars[3];
    memcpy(monthChars, _date_time+4, 2);
    monthChars[2] = 0;
    uint32_t months = atoi(monthChars) - 1;
    
    char daysChars[3];
    memcpy(daysChars, _date_time+6, 2);
    daysChars[2] = 0;
    uint32_t days = atoi(daysChars);
    
    uint32_t date = years*372 + months*31 + days;
    
    uintWrite.integerValue = date;
    out.write(uintWrite.chars, sizeof(uint32_t));
    
    dblWrite.doubleValue = _vwap;
    out.write(uintWrite.chars, sizeof(double));
    
    uintWrite.integerValue = _volume;
    out.write(uintWrite.chars, sizeof(uint32_t));
    
    dblWrite.doubleValue = _f2;
    out.write(uintWrite.chars, sizeof(double));
}
void binary_reader::stock_data::write_raw( std::ofstream& out )
{	
    DblUnion dblWrite;
    UintUnion uintWrite;
    
	out.write(_stock_name, sizeof(_stock_name));
    out.write(_date_time, sizeof(_date_time));
    
    dblWrite.doubleValue = _price;
    out.write(dblWrite.chars, sizeof(double));
    
    dblWrite.doubleValue = _vwap;
    out.write(dblWrite.chars, sizeof(double));
    
    uintWrite.integerValue = _volume;
    out.write(dblWrite.chars, sizeof(uint32_t));
    
    dblWrite.doubleValue = _f1;
    out.write(dblWrite.chars, sizeof(double));
    
    dblWrite.doubleValue = _t1;
    out.write(dblWrite.chars, sizeof(double));
    
    dblWrite.doubleValue = _f2;
    out.write(dblWrite.chars, sizeof(double));
    
    dblWrite.doubleValue = _f3;
    out.write(dblWrite.chars, sizeof(double));
    
    dblWrite.doubleValue = _f4;
    out.write(dblWrite.chars, sizeof(double));
}
