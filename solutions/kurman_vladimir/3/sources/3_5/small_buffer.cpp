#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <future>
#include <sstream>
#include <iomanip>
#include <market_message.h>
#include "../utility/rvref_wrapper.h"

void SmallBufferFunc(rvref_wrapper<std::ifstream> rvfin, rvref_wrapper<std::string> rvfileNum)
{
	using namespace std;
	using namespace binary_reader;
	ifstream fin = rvfin.get();
	const string fileNum = rvfileNum.get();
	fin.seekg(0, ios::end);
	const size_t fileSize = fin.tellg();
	fin.seekg(0);
	size_t curPos = 0;
	boost::int64_t curTime = -1;
	unordered_map<boost::uint32_t, size_t> sizeByTypeForCurTime;
	unordered_map<boost::uint32_t, boost::uint32_t> numMessagesByType;
	unordered_map<boost::uint32_t, boost::uint32_t> numTimesByType;
	unordered_set<boost::uint32_t> curTimeHasMessageOfType;
	const boost::uint32_t maxBufSize = 2048;
	static const string outputFilePrefixName = BINARY_DIR "/output_";
	static const string outputFileSuffixName = ".txt";
	ofstream fout(outputFilePrefixName + fileNum + outputFileSuffixName, ios::binary);
	while (curPos < fileSize)
	{
		const market_message mes(fin);
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
		fout.write(reinterpret_cast<const char*>(&messageByType.first), sizeof(messageByType.first));
		const double ans = static_cast<double>(messageByType.second) / numTimesByType[messageByType.first];
		fout.write(reinterpret_cast<const char*>(&ans), sizeof(ans));
	}
	fin.close();
	fout.close();
}

int main()
{
	using namespace std;
	const string inputFilePrefixName = BINARY_DIR "/input_";
	const string inputFileSuffixName = ".txt";
	vector<future<void>> futures;
	for (int i = 1; i <= 999; ++i)
	{
		stringstream ss;
		ss.width(3);
		ss << setfill('0');
		ss << i;
		string fileNum;
		ss >> fileNum;
		ifstream fin(inputFilePrefixName + fileNum + inputFileSuffixName, ios::binary);
		if (!fin.is_open())
			continue;
		futures.push_back(async(&SmallBufferFunc, rvref(fin), rvref(fileNum)));
	}
	for (auto & ftr : futures)
		ftr.wait();
	return 0;
}

