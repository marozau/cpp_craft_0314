#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

//Рекурсивный спуск при условии присутствия смежного острова:справа || слева || снизу || сверху
void recursion(std::vector<std::string> &map, const int i, const int j, const char land, const char water){
	map[i][j]=water;
	if(j+1<(int)map[i].size() && map[i][j+1]==land) recursion(map, i, j+1, land, water);
	if(j-1>=0 && map[i][j-1]==land) recursion(map, i, j-1, land, water);
	if(i+1<(int)map.size() && map[i+1][j]==land) recursion(map, i+1, j, land, water);
	if(i-1>=0 && map[i-1][j]==land) recursion(map, i-1, j, land, water);
	return;
}

//Поиск островов используя рекурсивную функцию
int searchIslands(std::vector<std::string> &map){
	const char land='o';
	const char water='~';
	int count=0;

	for (size_t i = 0; i < map.size(); ++i) {
			for (size_t j = 0; j < map[i].size(); ++j) {
				if(map[i][j]==land) {count++; recursion(map, i, j, land, water);}
			}
		}

	return count;
}

//Создание карты
void createMap(std::fstream &fileIn, std::vector<std::string> &map){
	std::string buf;

	getline(fileIn, buf);
	if(!fileIn) {std::cout<<"There is no data in input file"<<std::endl; fileIn.close(); exit(1);}

	while(fileIn){
	map.push_back(buf);
	getline(fileIn, buf);
	}
}

int main(int argc, char **argv) {
	std::vector<std::string> map;

	std::fstream fileIn;
	fileIn.open("input.txt", std::ios::in);
	if(!fileIn) {std::cout<<"Error path for input.txt"<<std::endl; fileIn.close(); exit(1);}

	createMap(fileIn, map);

	std::fstream fileOut;
	fileOut.open("output.txt", std::ios::out);
	if(!fileOut) {std::cout<<"Error path for output.txt"<<std::endl; fileIn.close(); fileOut.close(); exit(1);}

	fileOut<<searchIslands(map)<<std::endl;

	fileIn.close();
	fileOut.close();

	return 0;
}
