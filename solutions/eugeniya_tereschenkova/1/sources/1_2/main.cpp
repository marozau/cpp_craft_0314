#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <algorithm>
#include <vector>
using namespace std;

namespace Constants_1_2
{
	static const int nPrecisionNumbers = 10000;
}

void get_Codes(ifstream& stream, vector<long long int>& vectCodes)
{
	int nCodesCount = 0;

	stream >> nCodesCount;
	if(stream.eof())
		return;

	static const int nMaxCodesCount = 1000000;
	if(nCodesCount <= 0 || nCodesCount > nMaxCodesCount)
		return;
	else
		vectCodes.reserve(nCodesCount);

	double Passw;
	for( int nI = 0; nI < nCodesCount && !stream.eof(); nI++) 
	{
		stream >> Passw;
		vectCodes.push_back(static_cast<long long int>(Passw*Constants_1_2::nPrecisionNumbers));
	}
	sort(vectCodes.begin(), vectCodes.end());
}

bool compare_CodesAndPasswords(ifstream& stream, const vector<long long int>& vectCodes) 
{
	static const char* outp_file = BINARY_DIR "/Output.txt";
	ofstream output_file( outp_file );
	if(!output_file.is_open())
	{
		cout << "Could not open output file" << endl;
		return false;
	}
	double Passw;
	static const string good = "YES";
	static const string bad  = "NO";
	while(!stream.eof())
	{
		stream >> Passw;     

		if(binary_search(vectCodes.begin(), vectCodes.end(), static_cast<long long int>(Passw*Constants_1_2::nPrecisionNumbers)))
			output_file << good << endl;
		else 
			output_file << bad << endl;
	}
	output_file.close();
	return true;
}

int main()
{
	static const char* Locale = "Russian";
	setlocale(LC_ALL, Locale);
	static const char* inp_file = BINARY_DIR "/Input.txt";
	ifstream input_file( inp_file );

	if(!input_file.is_open())
	{
		cout << "Could not open input file" << endl;
		return 1;
	} 
	vector<long long int> vectCodes;
	get_Codes(input_file, vectCodes);

	if(!compare_CodesAndPasswords(input_file, vectCodes))
	{
		input_file.close();
		return 1;
	}
	input_file.close();

	return 0;
}
