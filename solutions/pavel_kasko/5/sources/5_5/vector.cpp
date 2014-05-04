#include "vector.h"

#include <string>

namespace task5_5
{
	void instantiation_test();
}

void task5_5::instantiation_test()
{
	vector< int > vi;
	vector< std::string > vs;
	vector< char > vc;
	vector< vector< int > > vvi;

	vi.push_back( 5 );
	vi.insert( 0, 3 );
	vi[ 0 ];
	vi.resize( 0ul );
	vi.reserve( 0ul );
	vi.size();
	vi.capacity();
	vi.empty();

	vi.begin();
	vi.end();
}
