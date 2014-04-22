#include "market_message.h"
#include <iostream>
using namespace std;


bool is_good_type (const boost::uint32_t type, const boost::uint32_t type_min, const boost::uint32_t type_max)
{
	return ((type >= type_min) && (type <= type_max)) ;
} 

int main()
{
	static const char* inp_file = BINARY_DIR "/input.txt";
	ifstream input_file(inp_file, ios::binary);
  
	if (!input_file.is_open())
	{
		cout << "Could not open input file" << endl;
		return 1;
	}

	static const char* outp_file = BINARY_DIR "/output.txt";
	ofstream output_file(outp_file, ios::binary);
	static const boost::uint32_t type_min = 1u;
	static const boost::uint32_t type_max = 4u;
	boost::uint32_t cur_time = 0;
	static const long long N = static_cast<long long>(pow(10.0,16.0));
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
			if( mark_mes.check_time(cur_time) && is_good_type(mark_mes.type(), type_min, type_max))
				mark_mes.write(output_file);
			nMesCount++;
		}
	}
	catch(...) 
	{
		input_file.close();
		output_file.close();
		return 1;
	};
    
	input_file.close();
	output_file.close();
	return 0;
}