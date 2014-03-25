#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <future>
#include <stock_data.h>
#include "../utility/rvref_wrapper.h"

void BinaryDatafeedFunc(rvref_wrapper<std::vector<binary_reader::stock_data>> rvsd)
{
	using namespace std;
	using namespace binary_reader;
	const vector<stock_data> vsd = rvsd.get();
	ofstream fout(BINARY_DIR "/output_" + vsd.front().stock_name() + ".txt", ios::binary);
	for (const stock_data & sd : vsd)
		sd.write(fout);
	fout.close();
}

int main()
{
	using namespace std;
	using namespace binary_reader;
	ifstream fin(BINARY_DIR "/input.txt", ios::binary);
	if (!fin.is_open())
	{
		cout << "Something went wrong with input file\n";
		return 1;
	}
	fin.seekg(0, ios::end);
	size_t const fileSize = fin.tellg();
	fin.seekg(0);
	size_t curPos = 0;
	vector<stock_data> stockDatas;
	while (curPos < fileSize)
	{
		stockDatas.push_back(stock_data(fin));
		curPos += stockDatas.back().size();
	}
	fin.close();
	sort(stockDatas.begin(), stockDatas.end(), [](const stock_data & lhs, const stock_data & rhs)
	{
		return lhs.stock_name() < rhs.stock_name();
	});
	vector<vector<stock_data>> groupedStockDatas;
	vector<stock_data> vectOfStockDatas;
	vector<future<void>> futures;
	for (auto it = stockDatas.begin(); it != stockDatas.end(); ++it)
	{
		const bool firstStockData = it == stockDatas.cbegin();
		const bool anotherStockName = firstStockData ? true : (it - 1)->stock_name() != it->stock_name();
		if (anotherStockName || firstStockData)
		{
			if (!firstStockData)
				futures.push_back(async(&BinaryDatafeedFunc, rvref(groupedStockDatas.back())));
			vectOfStockDatas.clear();
			vectOfStockDatas.push_back(move(*it));
			groupedStockDatas.push_back(move(vectOfStockDatas));
		}
		else
			groupedStockDatas.back().push_back(move(*it));
	}
	if (!groupedStockDatas.empty())
		futures.push_back(async(&BinaryDatafeedFunc, rvref(groupedStockDatas.back())));
	for (auto & ftr : futures)
		ftr.wait();
	fin.close();
	return 0;
}