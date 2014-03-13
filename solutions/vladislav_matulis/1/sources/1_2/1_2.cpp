#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> Vector;

bool compare( const Vector &, const double );

int main()
{
	ifstream in( BINARY_DIR "/input.txt" );
	if ( !in.is_open() )
		return 1;
	size_t n;
	in >> n;
	Vector arr;
	for ( size_t i = 0; i < n; ++i )
	{
		double buf;
		in >> buf;
		arr.push_back( int( buf*10000 ) );
	}
	ofstream out( BINARY_DIR "/output.txt" );
	if ( !out.is_open() )
		return 1;
	while ( !in.eof() )
	{
		double buf;
		in >> buf;
		out << ( ( compare( arr, int(buf*10000) ) ) ? "YES" : "NO" ) << endl;
	}
	in.close();
	out.close();
	return 0;
}

bool compare ( const Vector &ar, const double elem )
{
	return ( find( ar.begin(), ar.end(), elem ) != ar.end() );  
}