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
	static const char* input_file = BINARY_DIR "/Input.txt";
	static const char* output_file = BINARY_DIR "/Output.txt";
}

void findAndMarkCurrentLand(vector<string>& str, size_t nI, size_t nJ)
{
	if(str[nI].at(nJ) == '~')
		return;
	str[nI].at(nJ) = '~';

	findAndMarkCurrentLand(str, nI + 1, nJ);
	findAndMarkCurrentLand(str, nI - 1, nJ);
	findAndMarkCurrentLand(str, nI, nJ + 1);
	findAndMarkCurrentLand(str, nI, nJ - 1);
}

void readFile(ifstream& stream, vector<string>& str)
{
  string line, lineFill;
  size_t lineLength = 0;
  size_t nI = 0;
  
  if(stream.eof())
    return;
  
  getline(stream, line);
	
  lineLength = line.length();
  for(nI = 0; nI < lineLength + 2; nI++)
    lineFill.append("~");

  str.push_back(lineFill);
  while(true)
  {
	line.append("~");
        str.push_back(static_cast<string>("~")+line);
	if (stream.eof())
		break;
    	getline(stream, line);
  }
  str.push_back(lineFill);
}

void findLand(vector<string>& str)
{
  ofstream output_file(Constants_1_3::output_file);
  size_t nI = 0, nJ = 0, count = 0;
	
  if(!output_file.is_open())
  {
		cout << "Could not open output file" << endl;
		return;
  }

  static const size_t columnCount = str.size();
  static const size_t rowCount = str[0].length();

  for(nI = 1; nI < columnCount-1; nI++)
  {
    for(nJ = 1; nJ < rowCount-1; nJ++)
		{
      if(str[nI][nJ] == 'o')
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
  ifstream input_file(Constants_1_3::input_file);
  vector<string> str;
	
  if(!input_file.is_open())
  {
		cout << "Could not open input file" << endl;
		return 1;
  }

  readFile(input_file, str);
  input_file.close();
	
  findLand(str);
  
  return 0;
}
