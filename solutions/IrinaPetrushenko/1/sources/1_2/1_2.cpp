#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>   
#include <set>
#include <stdlib.h>
#include <hash_set>
using namespace std;

namespace task2{
	const static int precision=4;
	const static char precision_point='.';
	
}

void modify (string & str){ 
	if (str.find(task2::precision_point)==string::npos) return;
	string::iterator it=str.end()-1;
	int num=0;
	while (it!=str.begin()){
		if (*it==task2::precision_point){
			if (num>task2::precision) str.erase(it+task2::precision+1,str.end());
			return;
		}
		num++;
		it--;
	}
}


int main(){
	ifstream in(BINARY_DIR"/input.txt");
    ofstream out(BINARY_DIR"/output.txt");
	
    if (in.is_open()){
		int n;
		string str;

        set<string> my_set;
		in>>n;
        for (int i=0;i<n;i++){
        		in>>str;
			modify(str);
			my_set.insert (str);
        }

		while (in>>str){
			modify(str);
			out << ( my_set.find(str) != my_set.end() ? "YES" : "NO" ) << endl;
		}
    }
	else{
		cerr<<"Input file was not opened"<<endl;
		return 1;
	}
	in.close();
	out.close();
}
