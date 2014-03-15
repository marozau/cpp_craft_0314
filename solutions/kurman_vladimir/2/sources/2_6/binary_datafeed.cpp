#include <fstream>
#include <iostream>
#include <algorithm>
#include "stock_data.h"

int main()
{
	using namespace std;
	using namespace binary_reader;
	ifstream fin(BINARY_DIR "/input.txt", ios::binary);
	ofstream fout(BINARY_DIR "/output.txt", ios::binary);
	if (!fin.is_open())
	{
		cout << "Something is wrong with input.txt file\n";
		return 1;
	}
	fin.seekg(0, ios::end);
	size_t const fileSize = fin.tellg();
	fin.seekg(0);
	size_t curPos = 0;
	while (curPos < fileSize)
	{
		stock_data sd(fin);
		curPos += sd.size();
		sd.write(fout);
	}
	fin.close();
	fout.close();
	return 0;
}