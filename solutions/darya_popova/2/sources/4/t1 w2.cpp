
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
	boost:: uint32_t T=0;
	while ( in.good() )
	{
		try
			{
				binary_reader:: market_message st(in); 
		
				if(!in.good()) break;
				if( st.check(T) ) 
						st.write(out);
				else 
						continue;
			}
		catch(...) {};
	}
	in.close();
	out.close();
	return 0;
}