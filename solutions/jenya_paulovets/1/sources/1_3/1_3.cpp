#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <vector>

//Рекурсивный спуск при условии присутствия смежного острова:справа || слева || снизу || сверху
void recursion(char **map, int i, int j, const int sizeR, const int sizeC){
	map[i][j]='~';
	if(j+1<sizeC && map[i][j+1]=='o') recursion(map, i, j+1, sizeR, sizeC);
	if(j-1>=0 && map[i][j-1]=='o') recursion(map, i, j-1, sizeR, sizeC);
	if(i+1<sizeR && map[i+1][j]=='o') recursion(map, i+1, j, sizeR, sizeC);
	if(i-1>=0 && map[i-1][j]=='o') recursion(map, i-1, j, sizeR, sizeC);
	return;
}

//Поиск островов использую рекурсивную функцию
int searchIslands(char **map, const size_t sizeR, const size_t sizeC){

	int count=0;

	for (size_t i = 0; i < sizeR; ++i) {
			for (size_t j = 0; j < sizeC; ++j) {
				if(map[i][j]=='o') {count++; recursion(map, i, j, sizeR, sizeC);}
			}
		}

	return count;
}

//Создается карта в виде двумерного массива
char ** createArrey(std::fstream &fileIn, size_t &sizeR, size_t &sizeC){
	std::vector<std::string> bufMap;
	std::string buf;
	char **map;

	getline(fileIn, buf);

	bufMap.push_back(buf);
	while(fileIn){
	getline(fileIn, buf);
	bufMap.push_back(buf);
	}

	sizeR=bufMap.size();
	sizeC=buf.size();

	map=new char*[sizeR];
	for(size_t i=0; i<bufMap.size(); i++){
		map[i]=new char[sizeC+1];
		(bufMap.at(i)).copy(map[i], sizeC, 0);
		map[i][sizeC]='\0';
	}

	return map;
}

int main(int argc, char **argv) {
	char **map;
	size_t sizeC, sizeR;

	std::fstream fileIn;
	fileIn.open( BINARY_DIR "/input.txt", std::ios::in);
	if(!fileIn) {std::cout<<"Opening error"<<std::endl; return(1);}

	map=createArrey(fileIn, sizeR, sizeC);

	std::fstream fileOut;
	fileOut.open( BINARY_DIR "/output.txt", std::ios::out);
	if(!fileOut) {std::cout<<"Opening error"<<std::endl; return(1);}

	fileOut<<searchIslands(map, sizeR, sizeC)<<std::endl;

	fileIn.close();
	fileOut.close();

	return 0;
}
