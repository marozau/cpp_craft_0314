#include "stock_data.h"

binary_reader::stock_data::stock_data( std::ifstream& _in )
    : m_price_(0)
    , m_vwap_(0)
    , m_volume_(0)
    , m_f1_(0)
    , m_t1_(0)
    , m_f2_(0)
    , m_f3_(0)
    , m_f4_(0)
{
    readArray<char>(_in, m_stock_name_, ms_stock_name_max_size);
    readArray<char>(_in, m_date_time_, ms_data_time_size);
    if (_in.eof())
    {
        throw std::exception("empty file");
    }
    m_price_ = readValue<double>(_in);
    m_vwap_ = readValue<double>(_in);
    m_volume_ = readValue<boost::uint32_t>(_in);
    m_f1_ = readValue<double>(_in);
    m_t1_ = readValue<double>(_in);
    m_f2_ = readValue<double>(_in);
    m_f3_ = readValue<double>(_in);
    m_f4_ = readValue<double>(_in);
}

binary_reader::stock_data::stock_data( const char* _stock_name,
                                      const char* _date_time,
                                      const double _price,
                                      const double _vwap,
                                      const boost::uint32_t _volume,
                                      const double _f1,
                                      const double _t1,
                                      const double _f2,
                                      const double _f3,
                                      const double _f4 )
    : m_price_(_price)
    , m_vwap_(_vwap)
    , m_volume_(_volume)
    , m_f1_(_f1)
    , m_t1_(_t1)
    , m_f2_(_f2)
    , m_f3_(_f3)
    , m_f4_(_f4)
{
    memmove( m_stock_name_, _stock_name, sizeof( _stock_name ) );
    memmove( m_date_time_, _date_time, sizeof( _stock_name ) );
}

binary_reader::stock_data::~stock_data()
{

}


void binary_reader::stock_data::write( std::ofstream& out ) const
{
    char stock_name[ms_new_stock_name_max_size];
    memset(stock_name, 0, sizeof(stock_name));
    memmove( stock_name, m_stock_name_, sizeof( m_stock_name_ ) );

    out.write(stock_name, ms_new_stock_name_max_size);

    const boost::uint32_t count_day = getCountDay();
    out.write(reinterpret_cast<const char*>(&count_day), sizeof(count_day));

    out.write(reinterpret_cast<const char*>(&m_vwap_), sizeof(m_vwap_));

    out.write(reinterpret_cast<const char*>(&m_volume_), sizeof(m_volume_));

    out.write(reinterpret_cast<const char*>(&m_f2_), sizeof(m_f2_));
}


void binary_reader::stock_data::write_raw( std::ofstream& out ) const
{	
	// your code. Can be emty
	// this method is used for testing. It writes data to the binary file without convertion.
}


boost::uint32_t binary_reader::stock_data::getCountDay() const
{
    uint32_t year = 0, month = 0, day = 0;

    sscanf_s( m_date_time_, "%4d%2d%2d" ,&year ,&month ,&day );

    return (year - 1) * ms_count_days_in_year + (month - 1) * ms_count_days_im_month + day;
}


