#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <algorithm>
using namespace std;


namespace Constants_1_1
{
	const char* input_file = SOURCE_DIR "/tests/1_1Input.txt";
	const char* output_file = SOURCE_DIR "/tests/1_1Output.txt";
	const string good = "YES";
	const string bad  = "NO";
	const char* Locale = "Russian";
	const size_t maxInputLen = 100000;
}

bool isSpaceSymb(const char& symb)
{
	switch(symb)
	{
	case ' ':
	case '-':
	case '\\':
		return 1;
	default:
		return 0;
	}
}

bool formatting_line(ifstream& stream, string& line)
{
	bool bReturn = true;
	getline(stream, line);
	if(line.empty())
		return bReturn;
	if(line.size() > Constants_1_1::maxInputLen)
		cout << "Could not open input file" << endl;
	line.erase(remove_if(line.begin(), line.end(), isSpaceSymb), line.end());
	transform(line.begin(), line.end(), line.begin(), tolower);
	return bReturn;
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