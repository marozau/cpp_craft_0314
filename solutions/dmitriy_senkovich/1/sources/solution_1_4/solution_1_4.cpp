#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>

using namespace std;

int main(){
	ifstream in(BINARY_DIR"/input.txt",ios::in);
	ofstream out(BINARY_DIR"/output.txt",ios::out);

	if (!in.is_open()||!out.is_open()){
		std::cerr<<"Error while opening files\n";
		return 1;
	}

	int n;
	in>>n;
	vector <long double> a;
	long double temp;
	while(n--){
		in>>temp;
		a.push_back(floor(10000*temp));
	}
	sort(a.begin(),a.end());
	while(!in.eof()){
		in>>temp;
		temp=floor(10000*temp);
		vector <long double>::iterator i=lower_bound(a.begin(),a.end(),temp);
		if( (i != a.end()) && (*i == temp) )
			out<<"Yes\n";
		else
			if(i != a.begin()){
				i--;
				if(*i == temp)
					out<<"Yes\n";
				else 
					out<<"No\n";
			}
			else
				out<<"No\n";
	}
	return 0;
}