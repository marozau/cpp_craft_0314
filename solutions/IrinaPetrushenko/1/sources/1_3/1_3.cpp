#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

namespace task3{
	const static char water='~';
	const static char ground='o';
}

void dfs (int i,size_t j,vector<string> & matrix, const int n, const size_t m){
	matrix[i][j]=task3::water; 
	if (i+1<n && matrix[i+1][j]==task3::ground) dfs  (i+1,j,matrix,n,m);
	if (i-1>=0 && matrix[i-1][j]==task3::ground) dfs  (i-1,j,matrix,n,m);
	if (j+1<m && matrix[i][j+1]==task3::ground) dfs  (i,j+1,matrix,n,m);
	if (j-1>=0 && matrix[i][j-1]==task3::ground) dfs  (i,j-1,matrix,n,m);
}
int main(){
	ifstream in(BINARY_DIR"/input.txt");
    ofstream out(BINARY_DIR"/output.txt");

 
    if (in.is_open()){
		string str;
		vector <string> matrix;
		int n=0;
		size_t m=0;

		int k=0;
		while (getline (in,str)){
			m=str.size();
			matrix.push_back(str);
			k++;
		}
		n=k;
		int ans=0;
		for (int i=0;i<n;i++)
			for (size_t j=0;j<m;j++)
				if (matrix[i][j]==task3::ground){
					dfs (i,j,matrix,n,m);
					ans++;
				}

		out<<ans<<endl;
	}
	else{
		cerr<<"Input file was not opened"<<endl;
		return 1;
	}
	in.close();
	out.close();
}
