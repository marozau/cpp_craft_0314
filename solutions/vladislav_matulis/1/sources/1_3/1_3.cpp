#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace my
{
	static int len;
	static int high;
}

void dfs( vector <string> &, int, int );

int main()
{
	ifstream in( SOURCE_DIR "/input.txt" );
	if ( !in.is_open() )
		return 0;
	int count = 0;
	vector<string> isles;
	while ( !in.eof() )
	{
		string buf;
		getline( in, buf );
		isles.push_back(buf);
	}
	in.close();
	my::len = isles[0].size();
	my::high = isles.size();
	for ( int i = 0; i < my::high; ++i )
		for ( int j = 0; j < my::len; ++j )
		{
			if (isles[i][j] == 'o')
			{
				dfs( isles, i, j );
				count++;
			}
		}
	ofstream out( SOURCE_DIR "output.txt" );
	if ( !out.is_open() )
		return 0;
	out << count;
	out.close();
	return 0;
}

void dfs( vector<string> &vs, int x, int y )
{
	if ( x < 0 || x == my::high || y < 0 || y == my::len )
		return;
	if ( vs[ x ][ y ] != 'o' ) 
		return;
	vs[ x ][ y ] = '~';
	dfs( vs, x + 1, y );
	dfs( vs, x - 1, y );
	dfs( vs, x, y + 1 );
	dfs( vs, x, y - 1 );
}