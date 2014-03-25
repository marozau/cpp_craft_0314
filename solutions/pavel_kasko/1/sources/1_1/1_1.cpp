#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

void RemoveUnusedChars(std::string& str ,const std::string& unused_ch)
{
	for(int i = 0; i < unused_ch.length(); ++i)
		str.erase(std::remove(std::begin(str), std::end(str), unused_ch[i]), std::end(str));
}

int main(int argc, char *argv[])
{
	const std::string unused_ch = " -\\";
	const int legthLimit = 100000;

	if(argc != 2)
	{
		std::cout << "There are should be one commandline argument(text file)\nExample: 1_1.exe input.txt"<< std::endl;
		return 1;
	}
	
	std::ifstream inputStream(argv[1]);
	std::ofstream outputStream("output.txt");
	std::string firstline;
	
	std::getline(inputStream, firstline);
	
	if(firstline.length() > legthLimit)
	{
		std::cout << "First line length should be less than " << legthLimit << std::endl;
		return 1;
	}

	//std::cout << firstline << std::endl;

	RemoveUnusedChars(firstline, unused_ch);
	std::transform(std::begin(firstline), std::end(firstline), std::begin(firstline), ::tolower);
	//std::cout << firstline << std::endl;

	std::string line;
	while(!std::getline(inputStream, line).eof())
	{
		//std::cout << line << std::endl;
		
		RemoveUnusedChars(line, unused_ch);
		std::transform(std::begin(line), std::end(line), std::begin(line), ::tolower);
		//std::cout << line << std::endl;

		std::reverse(std::begin(line), std::end(line));
		//std::cout << line << std::endl;

		if(firstline.find(line) != std::string::npos)
			outputStream << "YES\n";
		else
			outputStream << "NO\n";
	}

	inputStream.close();
	outputStream.close();
	return 0;
}

