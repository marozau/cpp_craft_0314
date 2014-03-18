
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

void round_4( double &a)
{
	a = floor(a*10000)/10000.0;
}

int main(int argc, char* argv[]) 
{
	 
	ifstream fin( BINARY_DIR "/input.txt" );
	if( !fin.is_open() )
	{
		cout<<"Can't open file!";
		return 1;
	} 
	
	int N;
	fin>>N;
	double s;
	vector <double> codes;
	for(int i=0; i<N; i++)
	{
		
		fin>>s;
		round_4(s);
		codes.push_back(s);
	}
	
	vector <double> pswd;
	while ( fin>>s )
	{
		round_4(s);
		pswd.push_back(s);
		
	}
	fin.close();

	ofstream fout( BINARY_DIR "/output.txt" );
	if( !fout.is_open() )
		return 1;
		

	for( vector < double > :: const_iterator it=pswd.cbegin(); it!=pswd.cend(); it++ )
		{
			if( find( codes.begin(), codes.end(), *it ) != codes.end()) 
				fout<<"YES"<<endl;
			else 
				fout<<"NO"<<endl;
		}
	
	fout.close();
	return 0;
}