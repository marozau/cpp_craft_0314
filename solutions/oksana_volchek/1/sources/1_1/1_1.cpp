#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string transform(string& oldStr){
	string newStr = "";
	for (string::iterator iter = oldStr.begin(); iter != oldStr.end(); ++iter){
		if (*iter != ' ' && *iter != '-' && *iter != '\\'){
			*iter = tolower(*iter);
			newStr.push_back(*iter);
		}
	}
	return newStr;
}

int main()
{
	setlocale(LC_ALL, "");

	ifstream filein;
	filein.open(BINARY_DIR "/input.txt");
	if (filein.is_open()){
		string elem;
		getline(filein, elem);
		string firstString = transform(elem);
		reverse(firstString.begin(), firstString.end());
		
		ofstream fileout;
		fileout.open(BINARY_DIR "/output.txt");
		while (getline(filein, elem)){
			elem = transform(elem);
			if (firstString.find(elem) != string::npos)
			{
				fileout << "YES" << endl;
			}
			else {
				fileout << "NO" << endl;
			}
		}
		filein.close();
	}
	else {
		cout << "Unable to open file input.txt!" << endl;
		return 1;
	}	
	return 0;
}

