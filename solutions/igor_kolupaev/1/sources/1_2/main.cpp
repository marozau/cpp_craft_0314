#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <exception>
#include <sstream>
#include <math.h>

using namespace std;

typedef unsigned long long key_t;
typedef set<key_t> keyset;

key_t double_2_key(const double d)
{
	return static_cast<key_t> (d * 10000);
}

void load_codes(istream& is, keyset& codes)
{
	int codes_count;

	is >> codes_count;

	while (codes_count-- > 0)
	{
		double d;
		is >> d;

		const key_t key = double_2_key(d);

		codes.insert(key);
	}
}

int main(int argc, char* argv[])
{
	ifstream input_file(BINARY_DIR "/input.txt");

	if (!input_file.is_open())
	{
		cerr << "Unable to open input.txt";
		return 1;
	}

	keyset codes;

	load_codes(input_file, codes);

	ofstream output_file(BINARY_DIR "/output.txt");

	while (!input_file.eof())
	{
		double d;
		input_file >> d;

		key_t key = double_2_key(d);

		if (codes.count(key) > 0)
		{
			output_file << "YES" << endl;
		}
		else
		{
			output_file << "NO" << endl;
		}
	}

	output_file.close();
	input_file.close();

	return 0;
}
