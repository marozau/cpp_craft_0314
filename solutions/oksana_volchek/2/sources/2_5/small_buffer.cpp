#include <fstream>
#include <iostream>
#include <map>
#include <boost/cstdint.hpp>
#include "market_message.h"

using namespace std;

namespace myConstants {
	const uint32_t maxSize = 2048;
}

int main()
{
	ifstream filein;
	filein.open(BINARY_DIR "/input.txt", ios::binary);
	if(!filein.is_open()){
		cerr << "Unable to open binary file input.txt!" << endl;
		return 1;
	}
	
	uint32_t currentTime;
	uint32_t currentType;
	map<uint32_t, map<uint32_t, pair<uint32_t, uint32_t>>> allTypes;
	// structure of allTypes: type => time => (number of messages, total length)
	while (!filein.eof()){
		binary_reader::market_message market(filein);
		if (filein.good() && market.len() <= myConstants::maxSize){ // to ensure that the input stream is alive and the message is short enough
			currentTime = market.time();
			currentType = market.type();
			cout << currentTime << "\t" << currentType << "\t" << market.len() << endl;
			if (!allTypes.count(currentType)){
				allTypes[currentType] = map<uint32_t, pair<uint32_t, uint32_t>>();
			}
			if (!allTypes[currentType].count(currentTime)){
				allTypes[currentType][currentTime] = make_pair(1, market.len());
			}
			else if (allTypes[currentType][currentTime].second + market.len() <= myConstants::maxSize){
				++allTypes[currentType][currentTime].first;
				allTypes[currentType][currentTime].second += market.len();
			}
		}
	}
	filein.close();

	ofstream fileout;
	fileout.open(BINARY_DIR "/output.txt", ios::binary);
	double numerator;
	double denominator;
	double average;
	for (map<uint32_t, map<uint32_t, pair<uint32_t, uint32_t>>>::iterator iter = allTypes.begin(); iter != allTypes.end(); ++iter){
		numerator = 0;
		currentType = iter->first;
		cout << currentType << endl;
		map<uint32_t, pair<uint32_t, uint32_t>> inner_map = iter->second;
		denominator = inner_map.size();
		for (map<uint32_t, pair<uint32_t, uint32_t>>::iterator inner_iter = inner_map.begin(); inner_iter != inner_map.end(); ++inner_iter){
			numerator += (inner_iter->second).first;
		}
		average = numerator / denominator;

		fileout.write(reinterpret_cast< char* >(&currentType), sizeof(currentType));
		fileout.write(reinterpret_cast< char* >(&average), sizeof(average));
	}
	fileout.close();

	return 0;
}