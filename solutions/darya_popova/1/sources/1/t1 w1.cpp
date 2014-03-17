
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void remove_unused( string& a)
{
	string res;
	for( string :: iterator it = a.begin(); it != a.end(); it++)
	{
		if ( (*it)!=' ' && (*it)!='-' && (*it)!='\\' ) 
		{
			res+=tolower(*it);
		}
	}

	a=res;
   
}

int main(int argc, char* argv[]) 
{
	setlocale( LC_ALL, "Russian" );

	string smain;
	 
	ifstream fin( BINARY_DIR "/input.txt" );
	if( !fin.is_open() )
	{
		cout<<"Can't open file!";
		return 1;
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
	fin.close();

	ofstream fout( BINARY_DIR "/output.txt" );
	if( !fout.is_open() )
		return 1;
		
	for( vector < string > :: const_iterator it=keys.cbegin(); it!=keys.cend(); it++ )
	{
			if( smain.find( *it ) != string::npos ) 
				fout<<"YES"<<endl;
			else 
				fout<<"NO"<<endl;
	}

	fout.close();
	return 0;
}