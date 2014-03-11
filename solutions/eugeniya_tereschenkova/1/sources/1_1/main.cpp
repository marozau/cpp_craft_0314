#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <algorithm>
using namespace std;

namespace Constants_1_1
{
	static const char* input_file = BINARY_DIR "/Input.txt";
	static const char* output_file = BINARY_DIR "/Output.txt";
	static const string good = "YES";
	static const string bad  = "NO";
	static const char* Locale = "Russian";
	static const size_t maxInputLen = 100000;
}

bool formatting_line(ifstream& stream, string& line)
{
	getline(stream, line);
	if(line.empty())
		return false;
	if(line.size() > Constants_1_1::maxInputLen)
	{
		cout << "Incorrect string" << endl;
		return false;
	}
	line.erase(remove_if(line.begin(), line.end(), [](const char symb){ return (symb == ' ') || (symb == '\\') || (symb == '-'); }), line.end());
	transform(line.begin(), line.end(), line.begin(), tolower);
	return true;
}

int main()
{
	setlocale(LC_ALL, Constants_1_1::Locale);
	ifstream input_file( Constants_1_1::input_file );
	string line, key;
	if(!input_file.is_open())
	{
		cout << "Could not open input file" << endl;
		return 1;
	}
	if(!input_file.eof())
	{
		if(!formatting_line(input_file, line))
		{
			input_file.close();
			return 1;
		}
		ofstream output_file( Constants_1_1::output_file );
		if(!output_file.is_open())
		{
			cout << "Could not open output file" << endl;
			input_file.close();
			return 1;
		}

		while(!input_file.eof())
		{
			formatting_line(input_file, key);
			if(key.empty())
				continue;
			reverse(key.begin(), key.end());
			
			(line.find(key) != string::npos) ? 
				output_file << Constants_1_1::good << endl	:
				output_file << Constants_1_1::bad << endl;
		}

		input_file.close();
		output_file.close();
	}

	return 0;
}
