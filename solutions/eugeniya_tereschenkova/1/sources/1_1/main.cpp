#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <algorithm>
using namespace std;

bool formatting_line(ifstream& stream, string& line)
{
	getline(stream, line);
	if(line.empty())
		return false;
	static const size_t maxInputLen = 100000;
	if(line.size() > maxInputLen)
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
	static const char* Locale = "Russian";
	setlocale(LC_ALL, Locale);
	static const char* inp_file = BINARY_DIR "/Input.txt";
	ifstream input_file( inp_file );
	if(!input_file.is_open())
	{
		cout << "Could not open input file" << endl;
		return 1;
	}
	string line;
	if(!input_file.eof())
	{
		if(!formatting_line(input_file, line))
		{
			input_file.close();
			return 1;
		}
		static const char* outp_file = BINARY_DIR "/Output.txt";
		ofstream output_file( outp_file );
		if(!output_file.is_open())
		{
			cout << "Could not open output file" << endl;
			input_file.close();
			return 1;
		}
    
		static const string good = "YES", bad  = "NO";
		string key;
		while(!input_file.eof())
		{
			formatting_line(input_file, key);
			if(key.empty())
				continue;
			reverse(key.begin(), key.end());
			
			(line.find(key) != string::npos) ? 
				output_file << good << endl	:
				output_file << bad << endl;
		}

		input_file.close();
		output_file.close();
	}

	return 0;
}
