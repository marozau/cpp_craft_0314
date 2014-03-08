#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct point{
	int x,y;
public:
	point(){ x=0; y=0; }

	point(int x, int y){ 
		point::x=x;
		point::y=y;
	}

	point up(){
		return point(x,y-1);
	}

	point down(){
		return point(x,y+1);
	}

	point left(){
		return point(x-1,y);
	}

	point right(){
		return point(x+1,y);
	}
};

void side(vector<string>& a, int n, int m, queue<point>& q, point& p){
	if(p.x<0||p.y<0||p.x>=n||p.y>=m)
		return;
	if(a[p.x][p.y]=='~')
		return;
	q.push( p );
	a[p.x][p.y]='~';
}

int main(){

	ifstream in;
	ofstream out;

	in.open(BINARY_DIR"/input.txt",ios_base::in);
	out.open(BINARY_DIR"/output.txt",ios_base::out);

	if(!in.is_open()||!out.is_open()){
		cerr<<"Error while opening files\n";
		return 1;
	}

	vector<string> a;
	int n,m,ans=0;
	string buf;

	try{
		while(!in.eof()){
			if(!(in>>buf))
				throw exception("Error while reading data\n");
			a.push_back(buf);
		}
	} 

	catch(exception& e){
		cerr<<e.what();
		return 1;
	}

	n=(int)a.size();
	m=(int)a[0].size();

	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			if(a[i][j]=='o'){
				a[i][j]='~';
				queue<point> q;
				q.push(point(i,j));
				while(!q.empty()){
					point start = q.front();
					q.pop();
					side(a, n, m, q, start.up());
					side(a, n, m, q, start.down());
					side(a, n, m, q, start.left());
					side(a, n, m, q, start.right());
					}
				ans++;
			}

	try{
		out<<ans;
	}

	catch(exception& e){
		cerr<<e.what();
		return 1;
	}

	in.close();
	out.close();

	return 0;
}