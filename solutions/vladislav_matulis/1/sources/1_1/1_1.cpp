#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void merger( string & );
bool pred( const char );

int main()
{
	setlocale( LC_ALL, "rus" );
	ifstream in( SOURCE_DIR  "/input.txt" );
	if ( !in.is_open() )
		return 0;
	string home;
	getline( in, home );
	reverse( home.begin(), home.end() );
	merger( home );
	ofstream out( SOURCE_DIR "/output.txt" );
	if ( !out.is_open() )
		return 0;
	while ( !in.eof() )
	{
		string buf;
		getline( in, buf );
		merger( buf );
		out << ( ( home.find( buf ) != string::npos ) ? "YES" : "NO" ) << endl;
	}
	in.close();
	out.close();
	return 0;
}

void merger( string &str )
{
	str.erase(remove_if(str.begin(), str.end(), pred), str.end());
	transform( str.begin(), str.end(), str.begin(), tolower );
}

bool pred( const char c )
{
	return ( c == ' ') || ( c == '-' ) || ( c == '\\' );
}
