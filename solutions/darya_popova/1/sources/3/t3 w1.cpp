#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

void bfs( vector < string > &maps, int x, int y)
{
	if(x<0 || y<0 || x==maps.size() || y==maps[0].size() ) return;
	if( maps[x][y]=='~' || maps[x][y]=='&') return;
	maps[x][y]='&';
	bfs( maps,x+1, y);
	bfs( maps,x-1, y);
	bfs( maps, x, y+1);
	bfs( maps, x, y-1);

}

int main(int argc, char* argv[]) 
{
	 
	ifstream fin( BINARY_DIR "/input.txt" );
	if( !fin.is_open() )
	{
		cout<<"Can't open file!";
	} 
	
	string s;
	vector <string> maps;
	int number=0;
	while ( getline( fin, s ) )
	{
		maps.push_back(s);
	}

	for(int i=0; i<maps.size(); i++)
		for(int j=0; j<maps[0].size(); j++)
		{
			if ( maps[i][j] == 'o' ) 
			{
				bfs( maps, i, j);
				++number;
			}
		}
	ofstream fout( SOURCE_DIR "/output.txt" );
	if( !fout.is_open() )
		return 0;

	fout<<number<<endl;
	
	fin.close();
	fout.close();
	return 0;
}