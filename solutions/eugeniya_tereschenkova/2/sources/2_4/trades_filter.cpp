#include "market_message.h"
#include <iostream>
using namespace std;

int main()
{
	static const char* inp_file = BINARY_DIR "/input.txt";
	ifstream input_file(inp_file, ios::binary);
  
	if (!input_file.is_open())
	{
		cout << "Could not open input file" << endl;
		return 1;
	}

	ofstream output_file(BINARY_DIR "/output.txt", ios::binary);
	boost::uint32_t cur_time = 0;
	static const boost::uint32_t type_min = 1u;
	static const boost::uint32_t type_max = 4u;
	static const long long int N = 10^16;
	int nMesCount = 0;
	
	try
	{    
		while (!input_file.eof())
		{
			if(nMesCount > N)
				throw logic_error("Input is incorrect count messages");
			binary_reader::market_message mark_mes(input_file);
			if (input_file.eof()) 
				break;
			if( mark_mes.check(cur_time, type_min, type_max) )
				mark_mes.write(output_file);
			nMesCount++;
		}
	}
	catch(exception &e) 
	{
		cout << e.what() << endl;
		input_file.close();
		output_file.close();
		return 1;
	};
    
	input_file.close();
	output_file.close();
	return 0;
}