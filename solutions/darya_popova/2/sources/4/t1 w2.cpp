
#include <iostream>
#include <string>
#include <fstream>
#include "market_message.h"

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
	boost:: uint32_t curr_time=0;
	while ( in.good() )
	{
		try
		{
			binary_reader:: market_message message(in); 
		
			if(!in.good()) break;
			if( message.check(curr_time) ) 
					message.write(out);

		}
		catch(...) {};
	}

	in.close();
	out.close();
	return 0;
}