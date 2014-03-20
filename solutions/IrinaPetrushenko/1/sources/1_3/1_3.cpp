#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

namespace task3{
	const static char water='~';
	const static char ground='o';
}

void dfs (const int i,const size_t j,vector<string> & matrix, const int n, const size_t m, ofstream & out){
	matrix[i][j]=task3::water; 
	if (i+1<n && matrix[i+1][j]==task3::ground) dfs  (i+1,j,matrix,n,m,out);
	if (i>=1 && matrix[i-1][j]==task3::ground) dfs  (i-1,j,matrix,n,m,out);
	if (j>=1 && matrix[i][j-1]==task3::ground) dfs  (i,j-1,matrix,n,m,out);
	if (j+1<m && matrix[i][j+1]==task3::ground) dfs  (i,j+1,matrix,n,m,out);
}

int main(){
	ifstream in(BINARY_DIR"/input.txt");
    ofstream out(BINARY_DIR"/output.txt");

 
    if (in.is_open()){

		string str;
		vector <string> matrix;
		size_t m=0;
		int n=0;

		while (getline (in,str)){
			m=str.size();
			matrix.push_back(str);
			n++;
		}

		int ans=0;
		for (int i=0;i<n;i++)
			for (size_t j=0;j<m;j++)
				if (matrix[i][j]==task3::ground){
					dfs (i,j,matrix,n,m,out);
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
