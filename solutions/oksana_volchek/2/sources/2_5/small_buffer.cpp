#include <fstream>
#include <iostream>
#include <map>
#include <boost/cstdint.hpp>
#include "market_message.h"

using namespace std;

namespace myConstants {
	const uint32_t maxSize = 2048;
}

const boost::uint32_t msgSize(const binary_reader::market_message& myClass){
	return sizeof(myClass.type()) + sizeof(myClass.time()) + sizeof(myClass.len()) + myClass.len();
}

int main()
{
	ifstream filein;
	filein.open(BINARY_DIR "/input.txt", ios::binary);
	if(!filein.is_open()){
		cerr << "Unable to open file input.txt!" << endl;
		return 1;
	}
	
	boost::uint32_t currentTime;
	boost::uint32_t currentType;
	map<boost::uint32_t, map<boost::uint32_t, pair<boost::uint32_t, boost::uint32_t>>> allTypes;
	// structure of allTypes: type => time => (number of messages, total length)
	while (!filein.eof()){
		binary_reader::market_message market(filein);
		if (filein.good() && msgSize(market) <= myConstants::maxSize){
			currentTime = market.time();
			currentType = market.type();
			if (!allTypes.count(currentType)){
				if (!allTypes[currentType].count(currentTime) && msgSize(market) <= myConstants::maxSize){
					allTypes[currentType] = map<boost::uint32_t, pair<boost::uint32_t, boost::uint32_t>>();
					allTypes[currentType][currentTime] = make_pair(1, msgSize(market));
				}
			}
			else if (allTypes[currentType][currentTime].second + msgSize(market) <= myConstants::maxSize){
				++allTypes[currentType][currentTime].first;
				allTypes[currentType][currentTime].second += msgSize(market);
			}
		}
	}
	filein.close();

	ofstream fileout;
	fileout.open(BINARY_DIR "/output.txt", ios::binary);
	double numerator;
	double average;
	for (map<boost::uint32_t, map<boost::uint32_t, pair<boost::uint32_t, boost::uint32_t>>>::iterator iter = allTypes.begin(); 
	   iter != allTypes.end(); ++iter){
		numerator = 0;
		currentType = iter->first;
		map<uint32_t, pair<boost::uint32_t, boost::uint32_t>> inner_map = iter->second;
		for (map<boost::uint32_t, pair<boost::uint32_t, boost::uint32_t>>::iterator inner_iter = inner_map.begin(); 
			inner_iter != inner_map.end(); ++inner_iter){
			numerator += (inner_iter->second).first;
		}
		average = numerator / inner_map.size();
//		cout << currentType << "\t" << average << endl;
		fileout.write(reinterpret_cast< char* >(&currentType), sizeof(currentType));
		fileout.write(reinterpret_cast< char* >(&average), sizeof(average));
	}
	fileout.close();

	return 0;
}