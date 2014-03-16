#include <fstream>
#include <iostream>
#include <set>

using namespace std;

void truncate(double& x)
{
	x = floor(x * 10000) / 10000; 
}

int main()
{
	ifstream filein;
	filein.open(BINARY_DIR "/input.txt");
	if (filein.is_open()){
		int countKeys;
		filein >> countKeys;
		
		int i = 0;
		double elem;
		set<double> keys;
		while (i < countKeys){
			filein >> elem;
			++i;
			truncate(elem);
			keys.insert(elem);
		}

		ofstream fileout;
		fileout.open(BINARY_DIR "/output.txt");
		while (filein >> elem){
			truncate(elem);
			if (keys.count(elem)){
				fileout << "YES" << endl;
			}
			else {
				fileout << "NO" << endl;
			}
		}
		filein.close();
		fileout.close();
	}
	else {
		cout << "Unable to open file input.txt!" << endl;
		return 1;
	}
	
	return 0;
}

