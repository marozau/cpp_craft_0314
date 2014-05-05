#include <stock_data.h>
#include <market_message.h>
#include <iostream>
#include <string>
#include <boost\format.hpp>
#include <boost\thread\thread.hpp>
#include <boost\thread\xtime.hpp>

boost::uint32_t GetMessageSize(const binary_reader::market_message& message);

struct TypesAndSeconds
{
	int types;
	int seconds;
};

class MultyBuffer
{
	typedef std::map<boost::uint32_t, TypesAndSeconds> Statistic;
	typedef std::map<boost::uint32_t, boost::int32_t> Sizes;

	boost::mutex _mutex;
	std::vector<uint32_t> curentTypes;

	void DoWork(const int i);

public:
	void Start(const int& count);
	void StatisticUp(boost::uint32_t type, const bool increase_sec, Statistic& statistic);
	void ShowStatictics(Statistic& statistic, std::ofstream& resFile);
};

void MultyBuffer::Start(const int& count)
{
	boost::thread_group threads;

	for (int i = 1; i <= count; ++i)
		threads.create_thread(boost::bind(&MultyBuffer::DoWork, this, i));

	threads.join_all();
}

void MultyBuffer::DoWork(const int i)
{
	const std::string num_part = boost::str(boost::format("%03u.txt") % i);
	const std::string inputFile = BINARY_DIR + std::string("/input_") + num_part;
	std::ifstream inputStream(inputFile , std::ios::binary);

	Statistic statistic;
	Sizes sizes;

	if(!inputStream.good())
	{
		std::cout << "Incorrect file path: " << inputFile << std::endl;
		return;
	}

	const std::string outputFile = BINARY_DIR + std::string("/output_") + num_part;
	std::ofstream outputStream(outputFile, std::ios::out | std::ios::binary);

	const boost::uint32_t treshold = 2048;
	boost::uint32_t currentTime = -1;
	int currentSize = 0;
	
	while (true)
	{
		binary_reader::market_message message(inputStream);

		if(inputStream.eof())
			break;

		const boost::uint32_t type = message.type();
		if (sizes.find(type) == sizes.end())
			sizes[type] = 0;

		const boost::uint32_t messageSize = GetMessageSize(message);

		if (message.time() == currentTime && ((sizes[type] + messageSize) <= treshold))
		{
			sizes[type] += messageSize;

			const bool incr_sec = std::find(curentTypes.begin(), curentTypes.end(), type) == curentTypes.end();
			StatisticUp(type, incr_sec, statistic);

		}
		else if ((sizes[type] + messageSize) <= treshold)
		{
			curentTypes.clear();
			currentTime = message.time();
			sizes[type] = messageSize;
			StatisticUp(type, true, statistic);
		}
		else
			continue;

		curentTypes.push_back(type);
	}

	inputStream.close();
	ShowStatictics(statistic, outputStream);
	outputStream.close();
}

void MultyBuffer::StatisticUp(boost::uint32_t type, const bool increase_sec, Statistic& statistic)
{
	if(increase_sec)
		statistic[type].seconds++;

	statistic[type].types++;
}

void MultyBuffer::ShowStatictics(Statistic& statistic, std::ofstream& resFile)
{
	for(auto i = statistic.begin(); i != statistic.end(); ++i)
	{
		const double average = static_cast<double>(i->second.types) / static_cast<double>( i->second.seconds);

		resFile.write( reinterpret_cast< const char* >(& ( i->first ) ), sizeof( boost::uint32_t ) );
		resFile.write( reinterpret_cast< const char* >( &average ), sizeof(double) );
	}
}

boost::uint32_t GetMessageSize(const binary_reader::market_message& message)
{
	return sizeof(boost::uint32_t) * 3 + message.len();
}

int main()
{
	const int count = 999; 
	MultyBuffer tf;
	tf.Start(count);
}
