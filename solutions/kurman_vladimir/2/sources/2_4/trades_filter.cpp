#include <fstream>
#include <iostream>
#include <algorithm>
#include <utility>
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
	boost::uint32_t curMaxTime = 0;
	pair<boost::uint32_t, boost::uint32_t> acceptedMinMaxTypes = make_pair(1, 4);
	boost::uint32_t const delay = 2;
	while (curPos < fileSize)
	{
		market_message mes(fin);
		curPos += mes.size();
		if (!(mes.type() >= acceptedMinMaxTypes.first && mes.type() <= acceptedMinMaxTypes.second))
			continue;
		if (curMaxTime >= delay && mes.time() <= curMaxTime - delay)
			continue;
		mes.write(fout);
		curMaxTime = max(curMaxTime, mes.time());
	}
	fin.close();
	fout.close();
	return 0;
}