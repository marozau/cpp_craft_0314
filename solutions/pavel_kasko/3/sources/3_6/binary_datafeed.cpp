#include <market_message.h>
#include <stock_data.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <boost\shared_ptr.hpp>
#include <boost\make_shared.hpp>

class Lesson3
{
	typedef std::map<std::string, boost::shared_ptr<std::ofstream>> StkCollection;
	StkCollection stock_collection1;

public:
	void DoWork();
	void Close(const StkCollection& collection);
};

void Lesson3::DoWork()
{
	std::ifstream inputStream(BINARY_DIR "/input.txt", std::ios::binary);
	if (!inputStream.good())
	{
		std::cout << "Incorrect file path: " << BINARY_DIR "/input.txt" << std::endl;
		return;
	}

	while (true)
	{
		binary_reader::stock_data stock_data(inputStream);

		if(inputStream.eof())
			break;

		const std::string file_name = BINARY_DIR + std::string("/output_") + std::string(stock_data.stock_name()) + std::string(".txt");
		const char* stock_name = stock_data.stock_name();

		if(stock_collection1.find(stock_name) == stock_collection1.end())
			stock_collection1[stock_name] = boost::make_shared<std::ofstream>(file_name, std::ios::out | std::ios::binary);

		stock_data.write(*stock_collection1[stock_name]);
	}
	inputStream.close();

	Close(stock_collection1);
}

void Lesson3::Close(const StkCollection& collection)
{
	for(auto i = collection.begin(); i != collection.end(); ++i)
		i->second->close();
}

int main()
{
	Lesson3 lesson3;
	lesson3.DoWork();
}

