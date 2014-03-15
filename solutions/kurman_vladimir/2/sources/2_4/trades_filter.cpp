#include <fstream>
#include <iostream>
#include <algorithm>
#include "market_message.h"

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
	boost::int64_t curMaxTime = 0;
	while (curPos < fileSize)
	{
		market_message mes(fin);
		curPos += mes.size();
		if (!(mes.type() >= 1 && mes.type() <= 4))
			continue;
		if (mes.time() <= curMaxTime - 2)
			continue;
		mes.write(fout);
		curMaxTime = max<boost::int64_t>(curMaxTime, mes.time());
	}
	fin.close();
	fout.close();
	return 0;
}