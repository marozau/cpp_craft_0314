//============================================================================
// Name        : 10.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>

bool isDon(char ch){
	return ch==32 || ch==45 || ch==92;
}

//Создается строка без разделителей в нижнем регистре
void createFirstLine(std::fstream &fileIn, std::string &firstLine){

		size_t i=0;

	    getline(fileIn, firstLine);
	    if(!fileIn){std::cout<<"There is no data in input file"<<std::endl; exit(1);}

	    firstLine.append("1");

		std::string::iterator begin=firstLine.begin();
		std::string::iterator end=firstLine.end();

		std::remove_if(begin, end, isDon);

		while(firstLine.at(i)!=49) i++;
		firstLine.erase(i);

		for(size_t j=0; j<firstLine.size(); j++) firstLine.at(j)=tolower(firstLine.at(j));
}

//Поиск инвертированных ключей в ранее созданной строке
void searchReverseKeys(std::fstream &fileIn, std::fstream &fileOut, std::string &firstLine){

	std::string key;

	std::string::iterator beginOfLine=firstLine.begin();
    std::string::iterator endOfLine=firstLine.end();

    fileIn>>key;
    if(!fileIn){std::cout<<"There is no keys in input file"<<std::endl; exit(1);}

	do{
		for(size_t j=0; j<key.size(); j++) key.at(j)=tolower(key.at(j));

		std::string::iterator beginOfKey=key.begin();
		std::string::iterator endOfKey=key.end();

		std::reverse(beginOfKey, endOfKey);

		if(std::search(beginOfLine, endOfLine, beginOfKey, endOfKey)==endOfLine) fileOut<<"NO"<<std::endl;
		else fileOut<<"YES"<<std::endl;
		fileIn>>key;
	}
	while(fileIn);
}


int main(int argc, char **argv) {
	std::string firstLine;

	std::fstream fileIn;
	fileIn.open( BINARY_DIR "/input.txt", std::ios::in);
	if(!fileIn) {std::cout<<"Error path for input file"<<std::endl; return(1);}

	createFirstLine(fileIn, firstLine);

	std::fstream fileOut;
	fileOut.open( BINARY_DIR "/output.txt", std::ios::out);
	if(!fileOut) {std::cout<<"Error path for output file"<<std::endl; return(1);}

	searchReverseKeys(fileIn, fileOut, firstLine);

	fileOut.close();
	fileIn.close();

	return 0;
}

