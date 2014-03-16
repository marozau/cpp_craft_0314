#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

//Задается точность числа
double changePrecision(const double number){
	int tmp=static_cast<int>(number);
	int tmp1=10000*(number-tmp);

	return tmp+static_cast<double>(tmp1)/10000;
}

//Поиск кодов в паролях
void searchPassInCodes(const size_t sizeCodes, std::fstream &fileIn, std::fstream &fileOut){

	std::vector<double> codes;
	std::vector<double> pass;
	size_t i=0;
	double tmp;

	while(fileIn){
		fileIn>>tmp;
		if(i==0 && !fileIn) {std::cout<<"There is no 'code' data in input file"<<std::endl; fileIn.close(); fileOut.close(); exit(1);}
		else if(i<=sizeCodes && !fileIn) {std::cout<<"There is no 'pass' data in input file"<<std::endl; fileIn.close(); fileOut.close(); exit(1);}
		tmp=changePrecision(tmp);
		if(i<sizeCodes) codes.push_back(tmp);
		else pass.push_back(tmp);
		i++;
	}

	for(std::vector<double>::iterator it=pass.begin(); it+1!=pass.end(); it++){
		if(std::find(codes.begin(), codes.end(), *it)==codes.end()) fileOut<<"NO"<<std::endl;
		else fileOut<<"YES"<<std::endl;
	}
}

int main(int argc, char **argv) {
	std::fstream fileIn;
	fileIn.open("input.txt", std::ios::in);
	if(!fileIn) {std::cout<<"Error path for input.txt"<<std::endl; fileIn.close(); exit(1);}

	size_t sizeCodes;
	fileIn>>sizeCodes;
	if(!fileIn){std::cout<<"There is no data in input file"<<std::endl; fileIn.close(); exit(1);}
	else if(sizeCodes==0) {std::cout<<"There is no codes data in input file"<<std::endl; fileIn.close(); exit(1);}

	std::fstream fileOut;
	fileOut.open("output.txt", std::ios::out);
	if(!fileOut) {std::cout<<"Error path for output.txt"<<std::endl; fileIn.close(); fileOut.close(); exit(1);}

	searchPassInCodes(sizeCodes, fileIn, fileOut);

	fileIn.close();
	fileOut.close();

	return 0;
}



