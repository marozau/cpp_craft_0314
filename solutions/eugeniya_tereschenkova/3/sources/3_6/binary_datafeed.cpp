#include <iostream>
#include "stock_data.h"
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

	static const char* outp_file = BINARY_DIR "/output.txt";
	ofstream output_file(outp_file, ios::binary);
	try
	{    
		while (!input_file.eof())
		{
			binary_reader::stock_data st_data(input_file);
			if (input_file.eof()) 
				break;
			st_data.write(output_file);
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

