#include <fstream>
#include <utility>
#include <sstream>
#include <future>
#include <market_message.h>
#include <iomanip>
#include "../utility/rvref_wrapper.h"

void TradesFilterFunc(rvref_wrapper<std::ifstream> rvfin, rvref_wrapper<std::string> rvfileNum)
{
	using namespace std;
	using namespace binary_reader;
	ifstream fin = rvfin.get();
	const string fileNum = rvfileNum.get();
	fin.seekg(0, ios::end);
	const size_t fileSize = fin.tellg();
	fin.seekg(0);
	size_t curPos = 0;
	boost::uint32_t curMaxTime = 0;
	static const pair<boost::uint32_t, boost::uint32_t> acceptedMinMaxTypes = make_pair(1, 4);
	static const boost::uint32_t delay = 2;
	static const string outputFilePrefixName = BINARY_DIR "/output_";
	static const string outputFileSuffixName = ".txt";
	ofstream fout(outputFilePrefixName + fileNum + outputFileSuffixName, ios::binary);
	while (curPos < fileSize)
	{
		const market_message mes(fin);
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
		futures.push_back(async(&TradesFilterFunc, rvref(fin), rvref(fileNum)));
	}
	for (auto & ftr : futures)
		ftr.wait();
	return 0;
}