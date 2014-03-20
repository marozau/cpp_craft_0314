#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
const string input_file_name = BINARY_DIR "/input.txt";
const string output_file_name = BINARY_DIR "/output.txt";

void removeSymbols( string& source)
{
	string result;

	string::iterator it = source.begin();
	string::iterator end = source.end();

	for( ; it != end ; ++it)
	{
		if ( (*it)!=' ' && (*it)!='-' && (*it)!='\\' ) 
		{
			result += tolower(*it);
		}
	}

	source.swap(result);
   
}

int main(int argc, char* argv[]) 
{
	setlocale( LC_ALL, "Russian" );

	string text;
	 
	ifstream inFile( input_file_name );

	if( !inFile.is_open() )
	{
		cout<<"error occured while opening file " << input_file_name;
		
		return 1;
	} 

	getline( inFile, text );
	removeSymbols(text);
	

	vector <string> keys;

	string key;
	while ( getline( inFile, key ) )
	{
		;
		removeSymbols( key );
		reverse( key.begin(), key.end());
		keys.push_back( key );
	}

	inFile.close();

	ofstream outFile( output_file_name );

	if( !outFile.is_open() )
	{
		cout<<"error occured while opening file " << output_file_name;
		return 1;
	}
	
	vector< string >::iterator it = keys.begin();
	vector< string >::iterator end = keys.end();

	for( ; it != end; ++it )
	{
			if( text.find( *it ) != string::npos )
			{
				outFile << "YES" << endl;
			}
			else
			{
				outFile << "NO" << endl;
			}
	}

	outFile.close();



	return 0;
}