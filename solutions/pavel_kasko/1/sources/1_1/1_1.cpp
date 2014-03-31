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
	
	std::ifstream inputStream(BINARY_DIR "/input.txt");
	std::ofstream outputStream(BINARY_DIR "/output.txt");
	std::string firstline;
	
    if(!inputStream.good())
    {
        std::cout << "Couldn't open files!\n";
        return 1;
    }
    
	std::getline(inputStream, firstline);
	
	if(firstline.length() > legthLimit)
	{
		std::cout << "First line length should be less than " << legthLimit << std::endl;
		return 1;
	}

	RemoveUnusedChars(firstline, unused_ch);
	std::transform(std::begin(firstline), std::end(firstline), std::begin(firstline), ::tolower);

	std::string line;
	while(!std::getline(inputStream, line).eof())
	{		
		RemoveUnusedChars(line, unused_ch);
		std::transform(std::begin(line), std::end(line), std::begin(line), ::tolower);

		std::reverse(std::begin(line), std::end(line));

		if(firstline.find(line) != std::string::npos)
			outputStream << "YES\n";
		else
			outputStream << "NO\n";
	}

	inputStream.close();
	outputStream.close();
	return 0;
}
