#include <iostream> 
#include <fstream>
#include <string> 
#include <stdio.h>
#include <algorithm> 
#include <stdlib.h>
using namespace std ;

bool is_should_delete (char c){
	return (c==' ' || c=='-' ||c=='\\' );
}

void my_tolower (string& s){
	for (std::string::iterator it=s.begin(); it!=s.end(); ++it)
		if (int(*it)<=int('ß') && int(*it)>=int('À')) *it='à'+(int(*it)-int('À')); 
		else if (int(*it)<=int('Z') && int(*it)>=int('A')) *it='a'+(int(*it)-int('A')); 
}



int main(){ 
	std::ifstream in( BINARY_DIR"/input.txt");
	std::ofstream out(BINARY_DIR"/output.txt");
	setlocale( LC_ALL, "Russian" );
	

	if (in.is_open()){
		string word;
		getline (in,word);
	
		word.erase(remove_if(word.begin(), word.end(),is_should_delete),word.end());
		my_tolower(word);
		reverse (word.begin(),word.end());
	
	
		string str_to_find;
		while (getline(in,str_to_find)){
			str_to_find.erase(remove_if(str_to_find.begin(), str_to_find.end(),is_should_delete),str_to_find.end());
			my_tolower(str_to_find);
			size_t found = word.find(str_to_find);
			if (found!=std::string::npos) out<<"YES"<<endl; else out<<"NO"<<endl;
		}
	}
	else{
		cerr<<"Input file was not opened"<<endl;
		return 1;
	}
	in.close();
	out.close();
}


