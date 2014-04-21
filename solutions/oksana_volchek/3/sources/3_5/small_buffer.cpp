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

typedef pair<boost::uint32_t, boost::uint32_t> pairValues;
typedef map<boost::uint32_t, pairValues> timeStorage;
typedef map<boost::uint32_t, timeStorage> typeStorage;


const boost::uint32_t msgSize(const binary_reader::market_message& myClass){
	return sizeof(myClass.type()) + sizeof(myClass.time()) + sizeof(myClass.len()) + myClass.len();
}

int getSaveMsg(string const& inputFile, string const& outputFile){
	ifstream filein;
	filein.open(BINARY_DIR "/" + inputFile, ios::binary);
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
				if (!allTypes.count(currentType)){
					if (!allTypes[currentType].count(currentTime) && msgSize(market) <= myConstants::maxSize){
						allTypes[currentType] = timeStorage();
						allTypes[currentType][currentTime] = make_pair(1, msgSize(market));
					}
				}
				else if (allTypes[currentType][currentTime].second + msgSize(market) <= myConstants::maxSize){
					++allTypes[currentType][currentTime].first;
					allTypes[currentType][currentTime].second += msgSize(market);
				}	
			}
		}
	}
	catch (...){
		cerr << "Error!!!" << endl;
	}
	filein.close();

	ofstream fileout;
	fileout.open(BINARY_DIR "/" + outputFile, ios::binary);
	double numerator;
	for (typeStorage::iterator iter = allTypes.begin(); 
	   iter != allTypes.end(); ++iter){
		numerator = 0;
		currentType = iter->first;
		timeStorage inner_map = iter->second;
		for (timeStorage::iterator inner_iter = inner_map.begin(); 
			inner_iter != inner_map.end(); ++inner_iter){
			numerator += (inner_iter->second).first;
		}
		const double average = numerator / inner_map.size();
		fileout.write(reinterpret_cast< char* >(&currentType), sizeof(currentType));
		fileout.write(reinterpret_cast< const char* >(&average), sizeof(average));
	}
	fileout.close();

	return 0;
}

int main()
{
	const boost::filesystem::path fullPath = boost::filesystem::system_complete(BINARY_DIR / boost::filesystem::path(".\\", boost::filesystem::native));
	const boost::filesystem::directory_iterator end;
	boost::filesystem::path name;
	boost::thread_group myThreads;
	for (boost::filesystem::directory_iterator it(fullPath); it != end; ++it) {
		name = *it;
		if (boost::regex_match(name.string(), myConstants::templateName)){
			const string thisInputFile = name.filename().string();
			string tmp = thisInputFile;
			const string thisOutputFile = tmp.replace(0, 2, "out");
			myThreads.create_thread(boost::bind(&getSaveMsg, thisInputFile, thisOutputFile));
		}
	}
	myThreads.join_all();

	return 0;
}
