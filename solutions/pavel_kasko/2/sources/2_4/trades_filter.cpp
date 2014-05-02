#include "market_message.h"
#include <iostream>
#include <algorithm>

int main()
{
	std::ifstream inputStream(BINARY_DIR "/input.txt", std::ios::binary);
	if(!inputStream.good())
	{
		std::cout << "Incorrect file path: " << BINARY_DIR "/input.txt" << std::endl;
		return 1;
	}

	std::ofstream outputStream(BINARY_DIR "/output.txt", std::ios::out | std::ios::binary);

	boost::int32_t maxTime = 0;
	const boost::uint32_t diff = 2;
	const boost::uint32_t minType = 1;
	const boost::uint32_t maxType = 4;

	while (true)
	{
		binary_reader::market_message message(inputStream);
		
		if(inputStream.eof())
			break;
		
		if(message.checkValidTime(maxTime, diff) && message.checkValidType(minType, maxType))
		{
			maxTime = std::max(maxTime, message.time());
			message.write(outputStream);
		}
	}

	inputStream.close();
	outputStream.close();
}

