#include <fstream>
#include <iostream>
#include <set>

using namespace std;

double truncate(double& x)
{
	return floor(x * 10000) / 10000; 
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
			keys.insert(truncate(elem));
		}

		ofstream fileout;
		fileout.open(BINARY_DIR "/output.txt");
		while (filein >> elem){
			if (keys.count(truncate(elem))){
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