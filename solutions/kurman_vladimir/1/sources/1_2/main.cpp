#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

bool equalDouble(double const l, double const r)
{
	return abs(l - r) < 0.0001;
}

int main(int argc, char* argv[])
{
	ifstream fin(BINARY_DIR "/input.txt");
	ofstream fout(BINARY_DIR "/output.txt");
	if (!fin.is_open())
	{
		cout << "Something is wrong with in/out files\n";
		return 1;
	}
	int n;
	fin >> n;
	vector<double> racioValues;
	double val;
	for (int i = 0; i < n; ++i)
	{
		fin >> val;
		racioValues.push_back(val);
	}
	std::sort(racioValues.begin(), racioValues.end());
	while (fin >> val)
	{
		auto er = lower_bound(racioValues.cbegin(), racioValues.cend(), val);
		if (er != racioValues.cend() && equalDouble(val, *er))
			fout << "YES";
		else if (er != racioValues.cbegin() && equalDouble(*(--er), val))
			fout << "YES";
		else
			fout << "NO";
		fout << endl;
	}
	fin.close();
	fout.close();
	return 0;
}
