
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void remove_unused( string& a)
{

	for( string :: iterator it = a.begin(); it != a.end(); it++)
	{
		if ( (*it)==' ' || (*it)=='-' || (*it)=='\\' ) 
		{
			a.erase(it);
			it--;
		}
		else *it=tolower(*it);
	}
   
}

int main(int argc, char* argv[]) 
{
	setlocale( LC_ALL, "Russian" );

	string smain;
	 
	ifstream fin( BINARY_DIR "/input.txt" );
	if( !fin.is_open() )
	{
		cout<<"Can't open file!";
	} 

	getline( fin, smain );
	remove_unused(smain);
	reverse( smain.begin(), smain.end());

	vector <string> keys;
	string s;
	while ( getline( fin, s ) )
	{
		remove_unused(s);
		keys.push_back( s );
	}

	ofstream fout( SOURCE_DIR "/output.txt" );
	if( !fout.is_open() )
		return 0;
		
	for( vector < string > :: const_iterator it=keys.cbegin(); it!=keys.cend(); it++ )
	{
			if( smain.find( *it ) != string::npos ) 
				fout<<"YES"<<endl;
			else fout<<"NO"<<endl;
	}

	
	fin.close();
	fout.close();
	return 0;
}