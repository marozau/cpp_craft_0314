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

void modify (string & str){ 
	if (str.find(".")==string::npos) return;
	string::iterator it=str.end()-1;
	int num=0;
	while (it!=str.begin()){
		if (*it=='.'){
			if (num>4) str.erase(it+5,str.end());
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
        int m=0;
		string str;
        double temp;
        hash_set<double> my_set;
        in>>n;
        for (int i=0;i<n;i++){
            in>>str;
			
			modify(str);
			temp=stof(str);
			my_set.insert (temp);
        }

		while (in>>str){
			modify(str);
			temp=stof(str);
			if (my_set.find(temp)!=my_set.end()) out<<"YES"<<endl; else out<<"NO"<<endl;
		}
    }
	else{
		cerr<<"Input file was not opened"<<endl;
		return 1;
	}
	in.close();
	out.close();
}