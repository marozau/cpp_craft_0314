#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const string input_file_name = BINARY_DIR "/input.txt";
const string output_file_name = BINARY_DIR "/output.txt";

const int PRECISION = 4;


void round (double& x, int precision)
{
	const int factor = 10; 
	int mul = 1;
   
	for (int i = 0; i < precision; i++)
	{
		mul *= factor;
	}

	if (x > 0)
	{
		x =  floor(x * mul  ) / mul;
	}
	else
	{
		x =  ceil(x * mul ) / mul;
	}
}

int main(int argc, char* argv[]) 
{
	 
	ifstream inFile( input_file_name );
	if( !inFile.is_open() )
	{
		cout<<"error occured while opening file " << input_file_name;
		return 1;
	} 
	
	int valuesCount ;
	inFile >> valuesCount;

	double value;
	vector <double> codes;

	for(int i = 0; i < valuesCount; ++i)
	{
		
		inFile >> value;

		round(value, PRECISION); 

		codes.push_back(value);
	}
	
	vector <double> passwords;

	while ( !inFile.eof() )
	{
		inFile >> value;
		round(value, PRECISION);
		passwords.push_back(value);
		
	}

	inFile.close();

	ofstream outFile( output_file_name );

	if( !outFile.is_open() )
	{
		cout<<"error occured while opening file " << output_file_name;
		return 1;
	}
	
	vector< double >::iterator it = passwords.begin();
	vector< double >::iterator it_end = passwords.end();

	for( ; it != it_end; ++it )
	{
		if( find( codes.begin(), codes.end(), (*it) ) != codes.end() )
		{
			outFile << "YES" << endl;
		}
		else
		{
			outFile << "NO" << endl;
		}
	}
	
	outFile.close();
	return 0;
}
