#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

void my_round ( double& d )
{
	d = floor( d * 10000 )/ 10000; 
}

int main()
{
	vector < double > code, password;
	size_t number;

	ifstream in( SOURCE_DIR "/input.txt" );

	if ( !in.is_open() )
		return 0;

	in >> number;
	for( size_t i = 0; i < number; i++ )
	{
		double temp;
		in >> temp;
		my_round( temp );
		code.push_back( temp );
	}

	while( !in.eof() )
	{
		double temp;
		in >> temp;
		my_round( temp );
		password.push_back( temp );
	}
	in.close();
	
	ofstream out( SOURCE_DIR "/output.txt" );
	if( !out.is_open() )
		return 0;

	for( vector < double > :: const_iterator it = password.cbegin(); it != password.cend(); it++ )
	{
		if ( find( code.begin(), code.end(), *it ) != code.end() )
			out << "YES" << endl;
		else 
			out << "NO" << endl;
	}
	out.close();

	return 0;
}