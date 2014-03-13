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

std::string removeletters( std::string &str){
    char trash[] = "/ -";
    for(std::size_t i = 0; i < strlen(trash); i++ ){
        str.erase( std::remove( str.begin(), str.end(), trash[i] ), str.end() ) ;
    }
    return str;
}

void removeTrash(std::vector<std::string> &target){
    std::for_each(target.begin(),target.end(),removeletters);
}

int main(){
    std::vector <std::string> strings;
    strings = readFromFile();
    std::ofstream output(BINARY_DIR"/output.txt");
    removeTrash(strings);
    if(strings.size() > 0)
        std::transform(strings[0].begin(), strings[0].end(), strings[0].begin(), tolower);

    for(std::size_t i = 1; i < strings.size(); i++){
        std::transform(strings[i].begin(), strings[i].end(), strings[i].begin(), tolower);
        std::reverse(strings[i].begin(), strings[i].end());
        if(strings[0].find(strings[i]) != std::string::npos)
            output << "YES"<< std::endl;
        else
            output << "NO" << std::endl;
    }
	return 0;	
}
