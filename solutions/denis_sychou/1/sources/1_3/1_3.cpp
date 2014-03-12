#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void bfs( vector < string > &map, const int i, const int j )
{
	if ( i < 0 || i == map.size() || j < 0 || j == map[0].size() )
		return;
	const char water = '~';
	if( map[i][j] == water )
		return;
	map[i][j] = water;
	bfs( map, i + 1, j );
	bfs( map, i - 1, j );
	bfs( map, i, j + 1 );
	bfs( map, i, j - 1 );

}

int main()
{
	vector < string > map;
	ifstream in( BINARY_DIR "/input.txt" );
	ofstream out( BINARY_DIR "/output.txt" );
	if( !in.is_open() )
		return 1;

	while( !in.eof() )
	{
		string buf;
		getline( in, buf );
		map.push_back( buf );
	}
	in.close();

	const size_t n = map.size();
	const size_t m = map.at(0).size();
	size_t result = 0;
	const char land = 'o';

	for ( int i = 0; i < n; ++i)
		for ( int j = 0; j < m; ++j)
			if ( map[i][j] == land ) 
			{
				bfs( map, i, j );
				++result;
			}
			

	out << result; 

	out.close();
	return 0;
}