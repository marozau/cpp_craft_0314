#include <iostream>
#include <fstream>
#include "stock_data.h"

int main()
{
	std::ifstream inputStream(BINARY_DIR "/input.txt", std::ios::binary);
	if (!inputStream.good())
	{
		std::cout << "Incorrect file path: " << BINARY_DIR "/input.txt" << std::endl;
		return 1;
	}

	std::ofstream outputStream(BINARY_DIR "/output.txt", std::ios::out | std::ios::binary);

	while (true)
	{
		binary_reader::stock_data stock_data(inputStream);
		
		if(inputStream.eof())
			break;
		
		stock_data.write(outputStream);
	}

	outputStream.close();
	inputStream.close();
}

