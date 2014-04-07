#include "stock_data.h"
#include "market_message.h"



binary_reader::stock_data::stock_data( std::ifstream& in )
{
	in.read(_stock_name,sizeof(_stock_name));
    in.read(_date_time, sizeof(_date_time));

    in.read( reinterpret_cast< char * >( &_price), sizeof(_price));
    in.read( reinterpret_cast< char * >( &_vwap), sizeof(_vwap));
    in.read( reinterpret_cast< char * >( &_volume), sizeof(_volume));
    in.read( reinterpret_cast< char * >( &_f1), sizeof(_f1));
    in.read( reinterpret_cast< char * >( &_t1), sizeof(_t1));
    in.read( reinterpret_cast< char * >( &_f2), sizeof(_f2));
    in.read( reinterpret_cast< char * >( &_f3), sizeof(_f3));
    in.read( reinterpret_cast< char * >( &_f4), sizeof(_f4));
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
                                      const double f4 ) : _price(price),_vwap(vwap),_volume(volume),_f1(f1),_t1(t1),_f2(f2),_f3(f3),_f4(f4)
{
	memcpy(_stock_name,stock_name,sizeof(_stock_name));
    memcpy(_date_time,date_time,sizeof(_date_time));
}

binary_reader::stock_data::~stock_data()
{

}

void binary_reader::stock_data::write( std::ofstream& out ) const
{
	out.write(_stock_name,9);
    
    uint32_t years,months,days;
    sscanf( _date_time, "%4d%2d%2d", &years, &months, &days);
    const uint32_t date = (years - 1)*372 + (months - 1)*31 + days;
    
    out.write( reinterpret_cast< const char * >( &date), sizeof(date));
    out.write( reinterpret_cast< const char * >( &_vwap), sizeof(_vwap));
    out.write( reinterpret_cast< const char * >( &_volume), sizeof(_volume));
    out.write( reinterpret_cast< const char * >( &_f2), sizeof(_f2));
}

void binary_reader::stock_data::write_raw( std::ofstream& out ) const
{
	out.write(_stock_name, sizeof(_stock_name));
    out.write(_date_time, sizeof(_date_time));
    
    out.write( reinterpret_cast< const char * >( &_price), sizeof(_price));
    out.write( reinterpret_cast< const char * >( &_vwap), sizeof(_vwap));
    out.write( reinterpret_cast< const char * >( &_volume), sizeof(_volume));
    out.write( reinterpret_cast< const char * >( &_f1), sizeof(_f1));
    out.write( reinterpret_cast< const char * >( &_t1), sizeof(_t1));
    out.write( reinterpret_cast< const char * >( &_f2), sizeof(_f2));
    out.write( reinterpret_cast< const char * >( &_f3), sizeof(_f3));
    out.write( reinterpret_cast< const char * >( &_f4), sizeof(_f4));

}
