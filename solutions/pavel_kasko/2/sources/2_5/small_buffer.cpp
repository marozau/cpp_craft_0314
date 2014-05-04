#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include "market_message.h"

struct TypesAndSeconds
{
	int types;
	int seconds;
};

typedef std::map<boost::uint32_t, TypesAndSeconds> Statistic;
typedef std::map<boost::uint32_t, boost::int32_t> Sizes;

void ShowStatictics(Statistic& statistic, std::ofstream& resFile);
uint32_t GetMessageSize(const binary_reader::market_message& message);

int main()
{
	std::ifstream inputStream(BINARY_DIR "/input.txt", std::ios::binary); //input_253
	if(!inputStream.good())
	{
		std::cout << "Incorrect file path: " << BINARY_DIR "/input.txt" << std::endl;
		return 1;
	}

	std::ofstream outputStream(BINARY_DIR "/output.txt", std::ios::out | std::ios::binary);

	const uint32_t treshold = 2048;
	Statistic statistic;
	boost::int32_t currentTime = -1;
	Sizes sizes;
	std::vector<uint32_t> curentTypes;

	while (true)
	{
		binary_reader::market_message message(inputStream);

		if(inputStream.eof())
			break;

		const boost::uint32_t type = message.type();
		if (sizes.find(type) == sizes.end())
			sizes[type] = 0;

		uint32_t messageSize = GetMessageSize(message);
		
		if (message.time() == currentTime && ((sizes[type] + messageSize) <= treshold))
		{
			sizes[type] += messageSize;
			
			if(std::find(curentTypes.begin(), curentTypes.end(), message.type()) == curentTypes.end())
				statistic[message.type()].seconds++;
		}
		else if ((sizes[type] + messageSize) <= treshold)
		{
			curentTypes.clear();
			currentTime = message.time();
			sizes[type] = messageSize;
			statistic[message.type()].seconds++;
		}
		else
			continue;

		curentTypes.push_back(message.type());
		statistic[message.type()].types++;
	}

	ShowStatictics(statistic, outputStream);

	inputStream.close();
	outputStream.close();
}

void ShowStatictics(Statistic& statistic, std::ofstream& resFile)
{
	for(auto i = statistic.begin(); i != statistic.end(); ++i)
	{
		const double average = static_cast<double>(i->second.types) / static_cast<double>( i->second.seconds);

		resFile.write( reinterpret_cast< const char* >(& ( i->first ) ), sizeof( boost::uint32_t ) );
		resFile.write( reinterpret_cast< const char* >( &average ), sizeof(double) );
	}
}

uint32_t GetMessageSize(const binary_reader::market_message& message)
{
	return sizeof(boost::uint32_t) * 3 + message.len();
}
