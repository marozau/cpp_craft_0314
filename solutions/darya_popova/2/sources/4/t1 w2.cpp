#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "market_message.h"

using namespace std;


int main(int argc, char* argv[]) 
{
	 
	ifstream in( BINARY_DIR "/input.txt", ios:: binary ); 
	if( !in.is_open() )
	{
		cout<<"Can't open file!";
		return 1;
	} 
	ofstream out( BINARY_DIR "/output.txt", ios:: binary ); 
	boost:: uint32_t T=0;
	while ( !in.good() )
	{
		binary_reader:: market_message start(in); 
		if(!in.good()) break;
		if (start.type()<1 || start.type()>4) continue;

			if (T<start.time()) 
			{
				T=start.time();
				start.write( out);
			}
			else
			{
				if( start.time()+2>=T)
				{
					start.write(out);
				}
				else 
					continue;
			}
	}
	in.close();
	out.close();
	return 0;
}