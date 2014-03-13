#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

bool isDon(char ch){
	return ch==32 || ch==45 || ch==92;
}

//Создается строка без разделителей в нижнем регистре
void createFirstLine(std::fstream &fileIn, std::string &firstLine){

	    getline(fileIn, firstLine);
	    if(!fileIn){std::cout<<"There is no data in input file"<<std::endl; fileIn.close(); exit(1);}

		firstLine.erase(std::remove_if(firstLine.begin(), firstLine.end(), isDon), firstLine.end());

		std::transform(firstLine.begin(), firstLine.end(), firstLine.begin(), tolower);
}

//Поиск инвертированных ключей в ранее созданной строке
void searchReverseKeys(std::fstream &fileIn, std::fstream &fileOut, std::string &firstLine){

	std::string key;

	std::string::iterator beginOfLine=firstLine.begin();
    std::string::iterator endOfLine=firstLine.end();

    getline(fileIn, key);
    if(!fileIn){std::cout<<"There is no keys in input file"<<std::endl; fileIn.close(); fileOut.close(); exit(1);}

	do{
		key.erase(std::remove_if(key.begin(), key.end(), isDon), key.end());
		std::transform(key.begin(), key.end(), key.begin(), tolower);

		std::reverse(key.begin(), key.end());

		if(std::search(beginOfLine, endOfLine, key.begin(), key.end())==endOfLine) fileOut<<"NO"<<std::endl;
		else fileOut<<"YES"<<std::endl;
		getline(fileIn, key);
	}
	while(fileIn);
}


int main(int argc, char **argv) {
	std::string firstLine;

	std::fstream fileIn;
	fileIn.open("input.txt", std::ios::in);
	if(!fileIn) {std::cout<<"Error path for input file"<<std::endl; fileIn.close(); exit(1);}

	createFirstLine(fileIn, firstLine);

	std::fstream fileOut;
	fileOut.open("output.txt", std::ios::out);
	if(!fileOut) {std::cout<<"Error path for output file"<<std::endl; fileIn.close(); fileOut.close(); exit(1);}

	searchReverseKeys(fileIn, fileOut, firstLine);

	fileOut.close();
	fileIn.close();

	return 0;
}

