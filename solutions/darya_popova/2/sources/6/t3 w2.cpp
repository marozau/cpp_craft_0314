#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include "stock_data.h"

using namespace std;


int main(int argc, char* argv[]) 
{
	 
	ifstream in( BINARY_DIR "/input.txt", ios:: binary ); 
	if( !in.is_open() )
	{
		cout<<"Can't open file!";
		return 1;
	} 

	vector <binary_reader:: stock_data> a; 
	
	while ( !in.good() )
	{
		binary_reader:: stock_data start(in);
		if(!in.good()) break;
		a.push_back(start);
	}
	in.close();


	ofstream out( BINARY_DIR "/output.txt", ios:: binary ); 
		
	for( vector <binary_reader:: stock_data > :: iterator it=a.begin(); it!=a.end(); it++ )
	{
			 (*it).write( out );
	}

	out.close();
	return 0;
}