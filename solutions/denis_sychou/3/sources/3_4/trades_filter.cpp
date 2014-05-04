#include <fstream>
#include <string>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <market_message.h>

class Solution
{
	const static boost::uint32_t max_type = 4,
								 min_type = 1,
								 time = 2,
								 max_count = 1000;
	
	std::string filename( const std::string &name, const size_t number ) const
	{
		char num [ 4 ];
		sprintf( num, "%03d", number ); 
		return ( BINARY_DIR + name + boost::lexical_cast<std::string>( num ) + ".txt" );
	}
	
	void process( const size_t count )
	{
		const static std::string input = "/input_", output = "/output_";
		
		std::ifstream in;
		std::ofstream out;

		in.open( filename( input, count ).c_str(), std::ios::binary );
				
		if( !in.is_open() )
		{
			return;
		}

		out.open( filename( output, count ).c_str(), std::ios::binary );
				
		boost::uint32_t current = 0;

		while( !in.eof() )
		{
			binary_reader::market_message temp( in );

			if( in.eof() )
				break;

			if( current < temp.time() )
				current = temp.time();

			if(  ( temp.time() + time <= current ) || ( temp.type() > max_type ) || ( temp.type() < min_type ) )
				continue;

			temp.write( out );
		}
		in.close();
		out.close();
		
	}

public:

	void run()
	{
		boost::thread_group tg;
		for( size_t count = 1; count < max_count; count++ )
			tg.create_thread(  boost::bind( &Solution::process, this, count ) );

		tg.join_all();
	}
};

int main()
{
	Solution s;
	s.run();

	return 0;
}

