#include <fstream>
#include <string>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <market_message.h>

class Solution
{
	const static boost::uint32_t max_count = 1000,
								 memory = 2048;
		
	std::string filename( const std::string &name, const size_t number ) const
	{
		char num [ 4 ];
		sprintf( num, "%03d", number ); 
		return ( BINARY_DIR + name + boost::lexical_cast<std::string>( num ) + ".txt" );
	}
	
	void process( const size_t count )
	{
		const std::string input = "/input_";
		const std::string output = "/output_";

		boost::uint32_t current = 0;
		std::ifstream in;
		std::ofstream out;

		in.open( filename( input, count ).c_str(), std::ios::binary );

		if( !in.is_open() )
		{
			return;
		}

		out.open( filename( output, count ).c_str(), std::ios::binary );
		
		typedef std::map < boost::uint32_t, size_t > type_map;
		
		type_map type_size, type_count, type_last, type_different;

		while( !in.eof() )
		{
			binary_reader::market_message temp( in );

			if( in.eof() )
				break;

			if( temp.time() != current )
			{
				type_size.clear();
				current = temp.time();
			}

			if( ( type_size[temp.type()] + temp.size() ) <= memory )
			{
				type_size[temp.type()] += temp.size();
				++type_count[temp.type()];
			}

			if( ( type_last.count( temp.type() ) == 0 ) || ( type_last[temp.type()] != current ) )
			{
				type_last[temp.type()] = current;
				++type_different[temp.type()];
			}
		}	
		in.close();

		for( type_map::const_iterator it = type_count.cbegin(); it != type_count.cend(); ++it )
		{
			const double count = static_cast< double > ( it->second ) / type_different[it->first];
			const boost::uint32_t type = it->first;
			out.write( reinterpret_cast< const char* >( &type ), sizeof( type ) );
			out.write( reinterpret_cast< const char* >( &count ), sizeof( count ) );
		}
		out.close();
					
	}
	
public:

	void run()
	{
		boost::thread_group tg;
		for( size_t count = 1; count < max_count; ++count )
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

