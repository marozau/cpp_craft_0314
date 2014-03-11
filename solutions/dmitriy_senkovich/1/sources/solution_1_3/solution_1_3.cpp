#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <iterator>
#include <fstream>

void cut_string( std::string& cs )
{
	std::string ss;
	for( std::string::iterator it = cs.begin(); it != cs.end(); ++it ){
			if( ( *it != ' ' ) && ( *it != '\\' ) && ( *it != '-' ) )
			{
				ss += ( *it >= 'À' && *it <= 'ß' ) ? *it - 'À' + 'à' : tolower( *it );
			}
	}

	cs = ss;
}

int main(){
	setlocale(LC_ALL,"Russian");
	std::ifstream in;
	std::ofstream out;

	in.open( BINARY_DIR"/input.txt", std::ios_base::in );
	out.open( BINARY_DIR"/output.txt", std::ios_base::out );

	if (!in.is_open()||!out.is_open()){
		std::cerr<<"Error while opening files\n";
		return 1;
	}

	std::string s, cs;
	
	getline( in, s );
	cut_string( s );

	while( !in.eof() && getline( in, cs ) ){
		if(cs[0]!='\0'){
			cut_string( cs );
			
			reverse(cs.begin(),cs.end());
			if((s.find(cs))!=( std::string::npos))
				out << "Yes\n";
			else 
				out << "No\n";
		}
	}

	in.close();
	out.close();

	return 0;
}