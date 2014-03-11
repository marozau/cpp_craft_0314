#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>
#define eps 0.0001
struct compare{
    bool operator()(const double x, const double y){
        if(x - y < eps)
            return false;
        else
            return true;
    }
};


int main(){
    std::ifstream input(BINARY_DIR  "/input.txt");
    size_t n;
    input >> n;
    std::set<double, compare> numbers;
    for (size_t var = 0; var < n; ++var) {
        double tmp;
        input >> tmp;
        numbers.insert(tmp);
    }

    std::ofstream output(BINARY_DIR"/output.txt");
    double pass;
    input >> pass;
    while(!input.eof()){
        if(numbers.find(pass) != numbers.end())
            output << "YES"<< std::endl;
        else
            output << "NO" << std::endl;
        input >> pass;
    }
	return 0;	
}
