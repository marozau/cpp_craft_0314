#include "market_message.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

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
	boost::int64_t curTime = -1;
	unordered_map<boost::uint32_t, size_t> sizeByTypeForCurTime;
	unordered_map<boost::uint32_t, boost::uint32_t> numMessagesByType;
	unordered_map<boost::uint32_t, boost::uint32_t> numTimesByType;
	unordered_set<boost::uint32_t> curTimeHasMessageOfType;
	boost::uint32_t const maxBufSize = 2048;
	while (curPos < fileSize)
	{
		market_message mes(fin);
		curPos += mes.size();
		if (curTime < mes.time())
		{
			sizeByTypeForCurTime.clear();
			for (auto timeHasMsg : curTimeHasMessageOfType)
				++numTimesByType[timeHasMsg];
			curTimeHasMessageOfType.clear();
		}
		curTime = mes.time();
		curTimeHasMessageOfType.insert(mes.type());
		auto newSizeForCurTimeAndType = sizeByTypeForCurTime[mes.type()] + mes.size();
		if (newSizeForCurTimeAndType <= maxBufSize)
		{
			sizeByTypeForCurTime[mes.type()] += mes.size();
			++numMessagesByType[mes.type()];
		}
	}
	for (auto timeHasMsg : curTimeHasMessageOfType)
		++numTimesByType[timeHasMsg];
	for (auto messageByType : numMessagesByType)
	{
		fout.write(reinterpret_cast<char const*>(&messageByType.first), sizeof(messageByType.first));
		double const ans = static_cast<double>(messageByType.second) / numTimesByType[messageByType.first];
		fout.write(reinterpret_cast<char const*>(&ans), sizeof(ans));
	}
	fin.close();
	fout.close();
	return 0;
}

