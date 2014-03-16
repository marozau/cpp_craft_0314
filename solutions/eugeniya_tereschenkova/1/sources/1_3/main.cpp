#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;

namespace Constants_1_3
{
	static const char tilde = '~';
}

void findAndMarkCurrentLand(vector<string>& str, const size_t nI, const size_t nJ)
{
	if(str[nI].at(nJ) == Constants_1_3::tilde)
		return;
	str[nI].at(nJ) = Constants_1_3::tilde;

	findAndMarkCurrentLand(str, nI + 1, nJ);
	findAndMarkCurrentLand(str, nI - 1, nJ);
	findAndMarkCurrentLand(str, nI, nJ + 1);
	findAndMarkCurrentLand(str, nI, nJ - 1);
}

void readFile(ifstream& stream, vector<string>& str)
{  
	if(stream.eof())
		return;
	
	string line;
	getline(stream, line);

	const size_t lineLength = line.length();
	
	string lineFill;
	for(size_t nI = 0; nI < lineLength + 2; nI++)
		lineFill.append(1, Constants_1_3::tilde);
	
	str.push_back(lineFill);
	
	while(true)
	{
		line.append(1, Constants_1_3::tilde);
		str.push_back(Constants_1_3::tilde+line);
		if (stream.eof())
			break;
		getline(stream, line);
	}
	str.push_back(lineFill);
}

void findLand(vector<string>& str)
{
	static const char* outp_file = BINARY_DIR "/Output.txt";
	ofstream output_file(outp_file);
	if(!output_file.is_open())
	{
		cout << "Could not open output file" << endl;
		return;
	}
	
	static const size_t columnCount = str.size();
	static const size_t rowCount = str[0].length();
	size_t count = 0;
	static const char o = 'o';
	
	for(size_t nI = 1; nI < columnCount-1; nI++)
	{
		for(size_t nJ = 1; nJ < rowCount-1; nJ++)
		{
			if(str[nI][nJ] == o)
			{
				findAndMarkCurrentLand(str, nI, nJ);
				count++;
			}
		}
	}
	output_file << count;
	output_file.close();
}

int main()
{
	static const char* inp_file = BINARY_DIR "/Input.txt";
	ifstream input_file(inp_file);
	if(!input_file.is_open())
	{
		cout << "Could not open input file" << endl;
		return 1;
	}
	
	vector<string> str;
	readFile(input_file, str);
	input_file.close();
	
	findLand(str);
	return 0;
}
