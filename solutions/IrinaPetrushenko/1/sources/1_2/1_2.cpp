#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;


namespace task2{
	const static double EPS=0.0001;
	
}
struct comparator {
	bool operator()(const double a, const double b){
		return (a-b>=task2::EPS);
    }
};

int main(){
	ifstream in(BINARY_DIR"/input.txt");
	ofstream out(BINARY_DIR"/output.txt");
	
    if (in.is_open()){
		int n;
		in>>n;
		
		double temp;
		set<double,comparator> my_set;
		
        	for (int i=0;i<n;i++){
            		in>>temp;
	            	my_set.insert (temp);
        	}

		while (in>>temp){
			out << ( my_set.find(temp) != my_set.end() ? "YES" : "NO" ) << endl;
		}
    }
	else{
		cerr<<"Input file was not opened"<<endl;
		return 1;
	}
	in.close();
	out.close();
}
