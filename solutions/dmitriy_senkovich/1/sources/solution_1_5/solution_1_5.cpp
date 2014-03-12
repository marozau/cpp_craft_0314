#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

void if_land( vector<string>& a, int n, int m, queue<vector<int>>& tabl, vector<int> curr, int side ){

	switch( side ){
	case 0:{
		if ( ( curr[0]-1 < 0 ) )
			return;
		if ( a[curr[0]-1][curr[1]] != 'o' )
			return;
		else{
			curr[0] = curr[0]-1;
			tabl.push( curr );
			a[curr[0]][curr[1]] = '~';
		}
		   }
		   break;
	case 1:{
		if ( ( curr[1]-1 < 0 ) )
			return;
		if ( a[curr[0]][curr[1]-1] != 'o' )
			return;
		else{
			curr[1] = curr[1] - 1;
 			tabl.push( curr );
			a[curr[0]][curr[1]] = '~';
		}
		   }
		   break;
	case 2:{
		if ( ( curr[0]+1 > n-1 ) )
			return;
		if ( a[curr[0]+1][curr[1]] != 'o' )
			return;
		else{
			curr[0] = curr[0]+1;
			tabl.push( curr );
			a[curr[0]][curr[1]] = '~';
		}
		   }
		   break;
	case 3:{
		if ( ( curr[1]+1 > m-1 ) )
			return;
		if ( a[curr[0]][curr[1]+1] != 'o' )
			return;
		else{
			curr[1] = curr[1]+1;
			tabl.push( curr );
			a[curr[0]][curr[1]] = '~';
		}
		   }
		   break;
	}

}

int main(){

	ifstream in;
	ofstream out;

	in.open( BINARY_DIR"/input.txt" );
	out.open( BINARY_DIR"/output.txt" );

	if( (!in.is_open()) || (!out.is_open()) ){
		cerr<<"Error while opening files\n";
		return 1;
	}

	vector<string> a;
	int n, m;
	int count = 0;
	string buff_str;

	while( !in.eof() ){
		in >> buff_str;
		a.push_back( buff_str );
	}

	n = (int)a.size();
	m = (int)a[0].size();

	for( int i = 0; i < n; i++ )
		for( int j = 0; j < m; j++ )
			if( a[i][j] == 'o' ){
				a[i][j] = '~';
				queue<vector<int>> ch;
				vector<int> first_vec;
				first_vec.push_back( i );
				first_vec.push_back( j );
				ch.push( first_vec );
				while( ch.size() ){
					vector<int> curr_vec = ch.front();
					if_land( a, n, m, ch, curr_vec, 0 );
					if_land( a, n, m, ch, curr_vec, 1 );
					if_land( a, n, m, ch, curr_vec, 2 );
					if_land( a, n, m, ch, curr_vec, 3 );
					ch.pop();
				}
				count++;
			}

	out << count;

	in.close();
	out.close();

	return 0;
}