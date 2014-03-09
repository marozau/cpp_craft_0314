#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void dfs( vector < string > &map, int i, int j )
{
	if ( i < 0 || i == map.size() || j < 0 || j == map[0].size() )
		return;
	if( map[i][j] == '~' )
		return;
	map[i][j] = '~';
	dfs( map, i + 1, j );
	dfs( map, i - 1, j );
	dfs( map, i, j + 1 );
	dfs( map, i, j - 1 );

}

int main()
{
	vector < string > map;
	ifstream in( SOURCE_DIR "/input.txt" );
	ofstream out( SOURCE_DIR "/output.txt" );
	if( !in.is_open() )
		return 0;

	while( !in.eof() )
	{
		string buf;
		getline( in, buf );
		map.push_back( buf );
	}
	in.close();

	size_t n, m;
	m = map.at(0).size();
	n = map.size();
	size_t result = 0;

	for ( size_t i = 0; i < n; ++i)
		for ( size_t j = 0; j < m; ++j)
			if ( map[i][j] == 'o' ) 
			{
				dfs( map, i, j );
				++result;
			}
			

	out << result; 

	out.close();
	return 0;
}