#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

void prepareString(wstring & str)
{
	str.erase(remove_if(str.begin(), str.end(), [](wchar_t const ch)
	{
		return ch == ' ' || ch == '\\' || ch == '-';
	}), str.end());
	for (wchar_t & ch : str)
		ch = tolower(ch);
}

void getlineFromFile(wifstream & is, wstring & str)
{
	getline(is, str);
	prepareString(str);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	wifstream fin(BINARY_DIR "/input.txt");
	ofstream fout(BINARY_DIR "/output.txt");
	if (!fin.is_open())
	{
		cout << "Something is wrong with in/out files\n";
		return 1;
	}
	wstring mainStr;
	getlineFromFile(fin, mainStr);
	reverse(mainStr.begin(), mainStr.end());
	while (!fin.eof())
	{
		wstring str;
		getlineFromFile(fin, str);
		if (!str.empty())
			fout << (mainStr.find(str) == wstring::npos ? "NO" : "YES") << endl;
	}
	fin.close();
	fout.close();
	return 0;
}
