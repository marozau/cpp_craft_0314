#include "test_registrator.h"

#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <boost/filesystem.hpp>

#include <stock_data.h>

namespace binary_data
{
	namespace tests_
	{
		namespace details
		{			
		}
	}
}

void binary_reader::tests_::test_stock_data()
{
	static const double eps = 0.0000001;
	std::string test_file_path = BINARY_DIR "/test_out.txt";
	BOOST_CHECK_NO_THROW( stock_data( "AAPL", "20130101", 100.0, 101.1, 20000, 1.1, 2.1, 2.2, 3.3, 4.4 ) );
	{
		std::ofstream out( test_file_path.c_str(), std::ios_base::binary );
		stock_data sd( "AAPL", "20130101", 100.0, 101.1, 20000, 1.1, 2.1, 2.2, 3.3, 4.4 );
		sd.write_raw( out );
		out.close();
	}
	{
		std::ifstream in( test_file_path.c_str(), std::ios_base::binary );
		stock_data sd( in );
		BOOST_CHECK_EQUAL( memcmp( sd.stock_name_, "AAPL", 4 ), 0 );
		BOOST_CHECK_EQUAL( memcmp( sd.date_time_, "20130101", 8 ), 0 );
		BOOST_CHECK_EQUAL( fabs( sd.price_ - 100.0 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.vwap_ - 101.1 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.f1_ - 1.1 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.t1_ - 2.1 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.f2_ - 2.2 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.f3_ - 3.3 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.f4_ - 4.4 ) < eps, true );
		BOOST_CHECK_EQUAL( sd.volume_, 20000 );
	}
	boost::filesystem::remove( test_file_path );

}

void binary_reader::tests_::generate_2_6_tests()
{
	{
		std::ofstream out( BINARY_DIR "/input_261.txt", std::ios_base::binary );
		stock_data( "AAPL", "20130101", 100.0, 101.1, 10000, 1.1, 2.1, 2.21, 3.3, 4.4 ).write_raw( out );
		stock_data( "CIA", "20130201", 100.0, 101.1, 20000, 1.1, 2.1, 2.22, 3.3, 4.4 ).write_raw( out );
		stock_data( "GOOG", "20130301", 100.0, 101.1, 30000, 1.1, 2.1, 2.23, 3.3, 4.4 ).write_raw( out );
		stock_data( "XLI", "20130401", 100.0, 101.1, 40000, 1.1, 2.1, 2.24, 3.3, 4.4 ).write_raw( out );
		stock_data( "FGD", "20130501", 100.0, 101.1, 50000, 1.1, 2.1, 2.25, 3.3, 4.4 ).write_raw( out );
		stock_data( "NET", "20130601", 100.0, 101.1, 60000, 1.1, 2.1, 2.26, 3.3, 4.4 ).write_raw( out );
		stock_data( "XLK", "20130701", 100.0, 101.1, 70000, 1.1, 2.1, 2.27, 3.3, 4.4 ).write_raw( out );
		out.close();

		std::ofstream out_compare( BINARY_DIR "/output_261.txt", std::ios_base::binary );
		stock_data( "AAPL", "20130101", 100.0, 101.1, 10000, 1.1, 2.1, 2.21, 3.3, 4.4 ).write( out_compare );
		stock_data( "CIA", "20130201", 100.0, 101.1, 20000, 1.1, 2.1, 2.22, 3.3, 4.4 ).write( out_compare );
		stock_data( "GOOG", "20130301", 100.0, 101.1, 30000, 1.1, 2.1, 2.23, 3.3, 4.4 ).write( out_compare );
		stock_data( "XLI", "20130401", 100.0, 101.1, 40000, 1.1, 2.1, 2.24, 3.3, 4.4 ).write( out_compare );
		stock_data( "FGD", "20130501", 100.0, 101.1, 50000, 1.1, 2.1, 2.25, 3.3, 4.4 ).write( out_compare );
		stock_data( "NET", "20130601", 100.0, 101.1, 60000, 1.1, 2.1, 2.26, 3.3, 4.4 ).write( out_compare );
		stock_data( "XLK", "20130701", 100.0, 101.1, 70000, 1.1, 2.1, 2.27, 3.3, 4.4 ).write( out_compare );
		out_compare.close();
	}
	{
		std::ofstream out( BINARY_DIR "/input_262.txt", std::ios_base::binary );
		std::ofstream out_compare( BINARY_DIR "/output_262.txt", std::ios_base::binary );
		for( boost::uint32_t i = 0; i < 1000000; ++i )
		{
			stock_data( "AAPL", "20130101", i * 100.0, i * 101.1, i * 10000, i * 1.1, i * 2.1, i * 2.21, i * 3.3, i * 4.4 ).write_raw( out );
			stock_data( "GOOG", "20130101", i * 100.0, i * 101.1, i * 10000, i * 1.1, i * 2.1, i * 2.21, i * 3.3, i * 4.4 ).write_raw( out );

			stock_data( "AAPL", "20130101", i * 100.0, i * 101.1, i * 10000, i * 1.1, i * 2.1, i * 2.21, i * 3.3, i * 4.4 ).write( out_compare );
			stock_data( "GOOG", "20130101", i * 100.0, i * 101.1, i * 10000, i * 1.1, i * 2.1, i * 2.21, i * 3.3, i * 4.4 ).write( out_compare );
		}
		out.close();
	}
}
