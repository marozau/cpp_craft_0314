#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

namespace task3{
	const static size_t N=1000;
	const static char water='~';
	const static char ground='o';
}

void dfs (int i,size_t j,bool ** was,bool ** matrix, int n, size_t m){
	was[i][j]=true; 
	if (i+1<n && matrix[i+1][j] && !was[i+1][j]) dfs  (i+1,j,was,matrix,n,m);
	if (i-1>=0 && matrix[i-1][j] && !was[i-1][j]) dfs  (i-1,j,was,matrix,n,m);
	if (j+1<m && matrix[i][j+1] && !was[i][j+1]) dfs  (i,j+1,was,matrix,n,m);
	if (j-1>=0 && matrix[i][j-1] && !was[i][j-1]) dfs  (i,j-1,was,matrix,n,m);
}
int main(){
	ifstream in(BINARY_DIR"/input.txt");
    ofstream out(BINARY_DIR"/output.txt");
 
    if (in.is_open()){
		string str;
		bool ** matrix = new bool * [task3::N];
		bool ** was = new bool * [task3::N];
		queue<pair<int,int> > myqueue;
		int n;
		size_t m;

		for (int i=0;i<task3::N;i++) {
			matrix[i]=new bool [task3::N];
			was[i]=new bool[task3::N];
			for (int j=0;j<task3::N;j++){
				matrix[i][j]=false;
				was[i][j]=false;
			}
		}
		int k=0;
		while (getline (in,str)){
			m=str.size();
			for (size_t j=0;j<m;j++) matrix[k][j]=(str[j]==task3::ground);
			k++;
		}

		n=k;
		int ans=0;

		for (int i=0;i<n;i++)
			for (size_t j=0;j<m;j++)
				if (!was[i][j] && matrix[i][j]){
					dfs (i,j,was,matrix,n,m);
					ans++;
				}

		out<<ans<<endl;
		for (int i=0;i<task3::N;i++){
			delete was[i];
			delete matrix[i];
		}
		delete [] was;
		delete [] matrix;
	}
	else{
		cerr<<"Input file was not opened"<<endl;
		return 1;
	}
	in.close();
	out.close();
}