#include <fstream>
#include <iostream>
#include "../binary_reader/market_message.h"

int main()
{
	using namespace std;
	using namespace binary_reader;
	ifstream fin(BINARY_DIR "/input.txt", ios::binary);
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
		market_message mes(fin);
		curPos += mes.size();
	}
}