#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "market_message.h"
#include <boost/cstdint.hpp>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace myConstants {
	const uint32_t maxSize = 2048;
	const boost::regex templateName(".+input_(\\d){3}\\.txt$");
}

namespace threadManagement {
	boost::mutex myMutex;
}

typedef pair<boost::uint32_t, boost::uint32_t> pairValues;
typedef map<boost::uint32_t, pairValues> timeStorage;
typedef map<boost::uint32_t, timeStorage> typeStorage;
typedef map<boost::uint32_t, map<boost::uint32_t, boost::uint32_t>> fullRes;

const boost::uint32_t msgSize(const binary_reader::market_message& myClass){
	return sizeof(myClass.type()) + sizeof(myClass.time()) + sizeof(myClass.len()) + myClass.len();
}

int saveMsg(string const& inputFile, fullRes& myMap){
	ifstream filein;
	filein.open(inputFile, ios::binary);
	if(!filein.is_open()){
		cerr << "Unable to open file input.txt!" << endl;
		exit(1);
	}

	boost::uint32_t currentTime;
	boost::uint32_t currentType;
	typeStorage allTypes;
	try {
		while (!filein.eof()){
			binary_reader::market_message market(filein);
			if (filein.good() && msgSize(market) <= myConstants::maxSize){
				currentTime = market.time();
				currentType = market.type();
				boost::mutex::scoped_lock lock(threadManagement::myMutex);
				// cout << currentType << "\t"  << currentTime << "\t" << market.len() << endl;
				if (!allTypes.count(currentType)){
					if (!allTypes[currentType].count(currentTime) && msgSize(market) <= myConstants::maxSize){
						allTypes[currentType] = timeStorage();
						allTypes[currentType][currentTime] = make_pair(1, msgSize(market));
						if (!myMap.count(currentType)){
							myMap[currentType][currentTime] = 1;
						}
						else { ++myMap[currentType][currentTime]; }
					}
				}
				else if (allTypes[currentType][currentTime].second + msgSize(market) <= myConstants::maxSize){
					++allTypes[currentType][currentTime].first;
					allTypes[currentType][currentTime].second += msgSize(market);
					++myMap[currentType][currentTime];
				}
			}
		}
	}
	catch (...){
		cerr << "Error!!!" << endl;
	}
	filein.close();

	return 0;
}

int main()
{
	const boost::filesystem::path fullPath = boost::filesystem::system_complete(boost::filesystem::path(".\\", boost::filesystem::native));
	const boost::filesystem::directory_iterator end;
	boost::filesystem::path name;
	boost::thread_group myThreads;
	fullRes allRes;
	for (boost::filesystem::directory_iterator it(fullPath); it != end; ++it) {
		name = *it;
		if (boost::regex_match(name.string(), myConstants::templateName)){
			const string thisInputFile = BINARY_DIR "/" + name.filename().string();
			myThreads.create_thread(boost::bind(&saveMsg, thisInputFile, boost::ref(allRes)));
		}
	}
	myThreads.join_all();

	ofstream fileout;
	fileout.open(BINARY_DIR "/output.txt", ios::binary);
	double numerator;
	for (fullRes::iterator iter = allRes.begin(); iter != allRes.end(); ++iter){
		numerator = 0;
		boost::uint32_t currentType = iter->first;
		map<boost::uint32_t, boost::uint32_t> inner_map = iter->second;
		for (map<boost::uint32_t, boost::uint32_t>::iterator inner_iter = inner_map.begin(); 
			inner_iter != inner_map.end(); ++inner_iter){
			numerator += inner_iter->second;
		}
		const double average = numerator / inner_map.size();
		// cout << currentType << "\t" << average << endl;
		fileout.write(reinterpret_cast< char* >(&currentType), sizeof(currentType));
		fileout.write(reinterpret_cast< const char* >(&average), sizeof(average));
	}
	fileout.close();

	return 0;
}
