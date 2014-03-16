#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <algorithm>
#include <vector>
using namespace std;

namespace Constants_1_2
{
	static const char* input_file = BINARY_DIR "/Input.txt";
	static const char* output_file = BINARY_DIR "/Output.txt";
	static const string good = "YES";
	static const string bad  = "NO";
	static const char* Locale = "Russian";
	static const int nPrecisionNumbers = 10000;
	static const int nMaxCodesCount = 1000000;
}

void get_Codes(ifstream& stream, vector<long long int>& vectCodes)
{
	int nCodesCount = 0, nI = 0;
	double Passw;

	stream >> nCodesCount;
	if(stream.eof())
		return;

	if(nCodesCount <= 0 || nCodesCount > Constants_1_2::nMaxCodesCount)
		return;
	else
		vectCodes.reserve(nCodesCount);

	for( nI = 0; nI < nCodesCount && !stream.eof(); nI++) 
	{
		stream >> Passw;
		vectCodes.push_back((long long int)(Passw*Constants_1_2::nPrecisionNumbers));
	}
	sort(vectCodes.begin(), vectCodes.end());
}

bool compare_CodesAndPasswords(ifstream& stream, const vector<long long int>& vectCodes) 
{
	ofstream output_file( Constants_1_2::output_file );
	double Passw;
	if(!output_file.is_open())
	{
		cout << "Could not open output file" << endl;
		return false;
	}
	while(!stream.eof())
	{
		stream >> Passw;     

		if(binary_search(vectCodes.begin(), vectCodes.end(), (long long int)(Passw*Constants_1_2::nPrecisionNumbers)))
			output_file << Constants_1_2::good << endl;
		else 
			output_file << Constants_1_2::bad << endl;
	}
	output_file.close();
	return true;
}

int main()
{
	setlocale(LC_ALL, Constants_1_2::Locale);
	ifstream input_file( Constants_1_2::input_file );
	vector<long long int> vectCodes;

	if(!input_file.is_open())
	{
		cout << "Could not open input file" << endl;
		return 1;
	} 
	get_Codes(input_file, vectCodes);

	if(!compare_CodesAndPasswords(input_file, vectCodes))
	{
		input_file.close();
		return 1;
	}
	input_file.close();

	return 0;
}
