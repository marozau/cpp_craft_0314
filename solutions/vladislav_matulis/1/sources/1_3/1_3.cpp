#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace my
{
	const char land = 'o';
	const char water = '~';
}

void dfs( vector <string> &, const int, const int, const int, const int);

int main()
{
	ifstream in( BINARY_DIR "/input.txt" );
	if ( !in.is_open() )
		return 1;
	vector<string> isles;
	while ( !in.eof() )
	{
		string buf;
		getline( in, buf );
		isles.push_back(buf);
	}
	in.close();
	const int len = isles[0].size();
	const int high = isles.size();
	int count = 0;
	for ( int i = 0; i < high; ++i )
		for ( int j = 0; j < len; ++j )
		{
			if ( isles[i][j] == my::land )
			{
				dfs( isles, i, j, high, len );
				count++;
			}
		}
	ofstream out( BINARY_DIR "/output.txt" );
	if ( !out.is_open() )
		return 1;
	out << count;
	out.close();
	return 0;
}

void dfs( vector<string> &vs, const int x, const int y, const int high, const int len )
{
	if ( x < 0 || x == high || y < 0 || y == len )
		return;
	if ( vs[ x ][ y ] != my::land ) 
		return;
	vs[ x ][ y ] = my::water;
	dfs( vs, x + 1, y, high, len );
	dfs( vs, x - 1, y, high, len );
	dfs( vs, x, y + 1, high, len );
	dfs( vs, x, y - 1, high, len );
}