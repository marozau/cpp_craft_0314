#include <stock_data.h>
#include <market_message.h>
#include <iostream>
#include <string>
#include <boost\format.hpp>
#include <boost\thread\thread.hpp>
#include <boost\thread\xtime.hpp>

class MultyTradesFilter
{
	boost::mutex _mutex;
	void DoWork(const int i);
public:
	void Start(const int count);
};

void MultyTradesFilter::Start(const int count)
{
	boost::thread_group threads;
	
	for(int i = 1; i <= count; ++i)
		threads.create_thread(boost::bind(&MultyTradesFilter::DoWork, this, i));

	threads.join_all();
}

void MultyTradesFilter::DoWork(const int i)
{
	const std::string num_part = boost::str(boost::format("%03u.txt") % i);
	const std::string inputFile = BINARY_DIR + std::string("/input_") + num_part;
	const std::string outputFile = BINARY_DIR + std::string("/output_") + num_part;

	std::ifstream inputStream(inputFile , std::ios::binary);
	if(!inputStream.good())
	{
		std::cout << "Incorrect file path: " << inputFile << std::endl;
		return;
	}

	std::ofstream outputStream(outputFile, std::ios::out | std::ios::binary);

	boost::uint32_t maxTime = 0;
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

int main()
{
	const int count = 999;
	MultyTradesFilter tf;
	tf.Start(count);
}