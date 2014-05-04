#ifndef _BINARY_READER_STOCK_DATA_H_
#define _BINARY_READER_STOCK_DATA_H_

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

namespace binary_reader
{
    class stock_data : virtual protected boost::noncopyable
    {
        static const int ms_stock_name_max_size = 8;
        static const int ms_data_time_size  = 8;
        static const int ms_new_stock_name_max_size = 9;
        static const boost::uint32_t ms_count_days_in_year = 372;
        static const boost::uint32_t ms_count_days_im_month = 31;

        char            m_stock_name_[ms_stock_name_max_size];
        char            m_date_time_[ms_data_time_size];
        double          m_price_;
        double          m_vwap_;
        boost::uint32_t m_volume_;
        double          m_f1_;
        double          m_t1_;
        double          m_f2_;
        double          m_f3_;
        double          m_f4_;

    public:
        explicit stock_data( std::ifstream& in );
        explicit stock_data( const char* stock_name,
            const char* date_time,
            const double price,
            const double vwap,
            const boost::uint32_t volume,
            const double f1,
            const double t1,
            const double f2,
            const double f3,
            const double f4 );		
        ~stock_data();

        void write( std::ofstream& out ) const;
        void write_raw( std::ofstream& out ) const;
        const char* getStockName() const { return m_stock_name_; }

    private:
        template<typename T> T readValue(std::ifstream& _in)
        {
            T result = 0;
            _in.read(reinterpret_cast<char*>(&result), sizeof(T));

            return result;
        }

        template<typename T> void readArray(std::ifstream& _in, T* _array, boost::uint32_t _size_array)
        {
            _in.read(_array, sizeof(T) * _size_array);
        }

        boost::uint32_t getCountDay() const;
    };
}

#endif // _BINARY_READER_STOCK_DATA_H_

