#include "stdafx.h"
#include <ostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void Inspect(std::vector<std::vector<int>> &matrix, int i, int j);
void ShowMatrix(std::vector<std::vector<int>> &matrix);

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout << "There are should be one commandline argument(text file)\nExample: 1_1.exe input.txt"<< std::endl;
		return 1;
	}

	std::vector<std::vector<int>> sea;
	std::ifstream inpusStream(argv[1]);
	std::ofstream outputStream("output.txt");
	int island_count = 0;

	std::string line;
	int row_count = -1;

	while(inpusStream >> line) //fill sea
	{
		row_count++;
		std::vector<int> new_row;
		sea.push_back(new_row);

		for(int i = 0; i < line.length(); ++i)
			sea[row_count].push_back(line[i] == 'o' ? 1 : 0);
	}

	//ShowMatrix(sea);

	for(int i = 0; i < sea.size(); ++i)
	{
		for(int j = 0; j < sea[i].size(); ++j)
		{
			if(sea[i][j] == 1)
			{
				Inspect(sea, i, j);
				island_count++;
				//ShowMatrix(sea);
			}
		}
	}

	outputStream << island_count; 
	return 0;
}

void Inspect(std::vector<std::vector<int>> &matrix, int i, int j)
{
	if(i < 0 || i >= matrix.size()) return;
	if(j < 0 || j >= matrix[0].size()) return;

	if(matrix[i][j] == 1)
	{
		matrix [i][j] = 0;

		Inspect(matrix, i + 1, j);
		Inspect(matrix, i, j + 1);
		Inspect(matrix, i - 1, j);
		Inspect(matrix, i, j - 1);
	}
}

void ShowMatrix(std::vector<std::vector<int>> &matrix)
{
	for(int i = 0; i < matrix.size(); ++i)
	{
		for(int j = 0; j < matrix[i].size(); ++j)
		{
			std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;
}
