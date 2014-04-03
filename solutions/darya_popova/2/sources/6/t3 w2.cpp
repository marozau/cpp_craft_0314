
#include <iostream>
#include <string>
#include <fstream>
#include <stdint.h>
#include "stock_data.h"

using namespace std;


int main(int argc, char* argv[]) 
{
	 
	ifstream in( BINARY_DIR "/input.txt", ios:: binary ); 
	if( !in.is_open() )
	{
		cout<<"Can't open file!";
		system("pause");
		return 1;
	} 
	ofstream out( BINARY_DIR "/output.txt", ios:: binary );
	
	while ( in.good() )
	{
		try
		{
			binary_reader:: stock_data message(in);
			message.write( out );
		}
		catch(...){}
		
	}
	in.close();
	out.close();
	return 0;
}