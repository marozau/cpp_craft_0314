#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class CFinder
{
private:
	std::vector<std::string> *area;
	size_t x;
	size_t y;

public:
	CFinder(std::vector<std::string> *area)
	{
		CFinder::area = area;
		y = area->size();
		if(y > 0)
			x = area->at(0).length();
	}
	
	void Conquistar(size_t x, size_t y);
};

int main( int argc, char* argv[] )
{
	std::ifstream input_file( SOURCE_DIR "/input3.txt" );
	std::vector<std::string> lines;

	if(input_file)
	{
		while( !input_file.eof() )
		{
			std::string line;
			std::getline( input_file, line );
			lines.push_back(line);
		}
		input_file.close();

		int count(0);

		CFinder finder(&lines);

		for(auto i = 0; i < lines.size(); i++)
		{
			for(auto j = 0; j < lines.at(i).length(); j++)
			{
				if(lines.at(i).at(j) == 'o')
				{
					count++;
					finder.Conquistar(j, i);
				}
			}
		}

		std::ofstream output_file( BINARY_DIR "/output3.txt" );

		output_file << count;

		output_file.close();
	}
}

void CFinder::Conquistar(size_t x, size_t y)
{
	this->area->at(y).at(x) = '1';

	if(x > 0)
	{
		if(this->area->at(y).at(x - 1) == 'o')
			this->Conquistar(x - 1, y);
	}

	if(x + 1 < this->x)
	{
		if(this->area->at(y).at(x + 1) == 'o')
			this->Conquistar(x + 1, y);
	}

	if(y > 0)
	{
		if(this->area->at(y - 1).at(x) == 'o')
			this->Conquistar(x, y - 1);
	}

	if(y + 1 < this->y)
	{
		if(this->area->at(y + 1).at(x) == 'o')
			this->Conquistar(x, y + 1);
	}
}