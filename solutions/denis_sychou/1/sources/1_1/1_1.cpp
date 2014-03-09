#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void modification( string& s )
{
	string temp;
	for( string :: iterator it = s.begin(); it != s.end(); it++ )
		if( ( *it != ' ') && ( *it != '-' ) && ( *it != '\\' ) )
			temp += tolower( *it );
	s = temp;
}

int main()
{
	setlocale( LC_ALL, "Russian" );
	string str;
	vector < string > keys;

	ifstream in( SOURCE_DIR "/input.txt" );
	if ( !in.is_open() )
		return 0;
	getline( in, str );
	modification( str );
	while( !in.eof() )
	{
		string temp;
		getline( in, temp );
		modification( temp );
		reverse( temp.begin(), temp.end() );
		keys.push_back(temp);
	}
	in.close();

	ofstream out( SOURCE_DIR "/output.txt" );
	if( !out.is_open() )
		return 0;
	for( vector < string > :: const_iterator it = keys.cbegin(); it != keys.cend(); it++ )
	{
		if( str.find( *it ) != string::npos )
			out << "YES" << endl;
		else
			out << "NO" << endl;
	}
	out.close();

	return 0;	
}