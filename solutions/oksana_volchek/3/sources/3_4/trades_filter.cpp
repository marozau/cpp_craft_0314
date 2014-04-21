/*
In my 3_4 and 3_5 CMake files, I use 
	link_directories(${Boost_LIBRARY_DIRS})
to ensure that the required Boost modules will be
linked as expected. Otherwise I get error LNK1004,
indicating that the system is unable to find some
Boost libraries (thread, regex, and their dependencies).
*/

#include <iostream>
#include <fstream>
#include <string>
#include "market_message.h"
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/cstdint.hpp>

using namespace std;

int deleteMsg(string const& nameFilein, string const& nameFileout){	
	ifstream in;
	in.open(BINARY_DIR "/" + nameFilein, ios::binary);
	if (!in.is_open()){
		cout << "Unable to open binary file " << nameFilein.c_str() << endl;
		return 1;
	}

	boost::uint32_t maxTime = 0;
	ofstream out;
	out.open(BINARY_DIR "/" + nameFileout, ios::binary);
	while (!in.eof()){
		try {
			binary_reader::market_message market(in);
			if (in.good() && market.type() >= 1 && market.type() <= 4){
				const boost::uint32_t this_time = market.time();
				if (this_time + 2 <= maxTime){
					continue;
				}
				else {
					market.write(out);
					if (market.time() > maxTime){
						maxTime = market.time();
					}
				}
			}
		}
		catch (...){
			cerr << "An error occurred while processing the input file!" << endl;
			return 1;
		}
	}
	in.close();
	out.close();

	return 0;
}

int main(){
	const boost::filesystem::path fullPath = boost::filesystem::system_complete(BINARY_DIR / boost::filesystem::path(".\\" , boost::filesystem::native));
	const boost::filesystem::directory_iterator end;
	const boost::regex templateName(".+input_(\\d){3}\\.txt$");
	boost::filesystem::path name;
	boost::thread_group myThreads;
	for (boost::filesystem::directory_iterator it(fullPath); it != end; ++it) {
		name = *it;
		if (boost::regex_match(name.string(), templateName)){
			const string inputFile = name.filename().string();
			string tmpName = inputFile;
			const string outputFile = tmpName.replace(0, 2, "out");
			myThreads.add_thread(new boost::thread(&deleteMsg, inputFile, outputFile));
		}
	}
	myThreads.join_all();
	
	return 0;
}
