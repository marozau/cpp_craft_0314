#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>

std::vector<std::string> readFromFile(){
    std::vector<std::string> allFile;
    std::ifstream input(BINARY_DIR  "/input.txt");
    std::string line;
    std::getline(input, line);
    while ( !input.eof()) {
        allFile.push_back(line);
        std::getline(input, line);
    }
    return allFile;
}


void markUp(std::vector<std::string>& strings, std::size_t i, std::size_t j){
    if(i >=0 && i< strings.size() && j>=0 && j< strings[i].size()){
        if(strings[i][j] == 'o'){
            strings[i][j] = '~';
            markUp(strings,i-1,j);
            markUp(strings,i,j+1);
            markUp(strings,i,j-1);
            markUp(strings,i+1,j);

        }
    }
}

int main(){
    std::vector <std::string> strings;
    strings = readFromFile();
    std::ofstream output(BINARY_DIR"/output.txt");
    std::size_t answer = 0;
    for(std::size_t i = 0; i < strings.size(); i++){
        for(std::size_t j = 0; j < strings[i].length(); j++){
            if(strings[i][j] == 'o'){
                markUp(strings, i, j);
                answer++;
            }
        }
    }
    output << answer;
	return 0;	
}
