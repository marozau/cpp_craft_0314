#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

void check(queue < pair <int,int> > & q, vector < string > &maps, const int x, const int y)
{
	if(x<0 || y<0 || x==maps.size() || y==maps[0].size() ) return ;
	if( maps[x][y]=='~' ) return;
	maps[x][y]='~';
	q.push(make_pair(x,y));
}

void bfs(vector < string > &maps, const int xs, const int ys)
{
	queue< pair <int,int> > q;
	q.push( make_pair(xs,ys) );
	while (!q.empty())
	{
		int x,y;
		pair <int,int> temp = q.front();
		q.pop();
		x = temp.first;
		y = temp.second;
		check(q, maps,x+1, y);
		check(q, maps,x-1, y);
		check(q, maps, x, y+1);
		check(q, maps, x, y-1);
	}	
}

int main(int argc, char* argv[]) 
{
	 
	ifstream fin( BINARY_DIR "/input.txt" );
	if( !fin.is_open() )
	{
		cout<<"Can't open file!";
		return 1;
	} 
	
	string s;
	vector <string> maps;
	while ( getline( fin, s ) )
	{
		maps.push_back(s);
	}
	fin.close();

	int number=0;
	for(size_t i=0; i<maps.size(); i++)
		for(size_t j=0; j<maps[0].size(); j++)
		{
			if ( maps[i][j] == 'o' ) 
			{
				bfs( maps, i, j);
				++number;
			}
		}
	ofstream fout( BINARY_DIR "/output.txt" );
	if( !fout.is_open() )
		return 1;

	fout<<number<<endl;
	
	fout.close();
	return 0;
}