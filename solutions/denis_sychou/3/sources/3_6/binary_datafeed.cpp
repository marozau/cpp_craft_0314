#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <stock_data.h>

std::string filename( const std::string &name, const std::string &stock_name )
{
	return ( BINARY_DIR + name + stock_name + ".txt" );
}

class Solution
{	
	std::ifstream in;
	
	typedef std::vector< binary_reader::stock_data > vect_msg;
	typedef std::map< std::string, vect_msg > storage;
	storage storage_;
		
	void process( const std::string& stock_name )
	{
		const std::string output = "/output_";
		std::ofstream out( filename( output, stock_name ), std::ios::binary );
		
		for( vect_msg::const_iterator it = storage_[ stock_name ].cbegin(); it != storage_[ stock_name ].cend(); it++ )
		{
			it->write( out );
		}

		out.close();
	}
	
public:

	Solution()
	{
		in.open( BINARY_DIR "/input.txt", std::ios::binary );
	}

	~Solution()
	{
		in.close();
	}

	void run()
	{
		
		while( !in.eof() )
		{
			binary_reader::stock_data temp( in );

			if( in.eof() )
				break;

			storage_[ temp.stock_name() ].push_back( temp );
		}
		
		boost::thread_group tg;
		for( storage::const_iterator it = storage_.cbegin(); it != storage_.cend(); it++ )
			tg.create_thread( boost::bind( &Solution::process, this, boost::ref( it->first ) ) );

		tg.join_all();
	}

};

int main()
{
	Solution s;
	s.run();

	return 0;
}

