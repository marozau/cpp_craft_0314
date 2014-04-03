#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

bool is_garbage(const char ch)
{
	return ch == ' ' || ch == '-' || ch == '\\';
}

void normalize(string& str)
{
	str.erase(remove_if(str.begin(), str.end(), is_garbage), str.end());
	transform(str.begin(), str.end(), str.begin(), ::toupper);
}

int main(int argc, char* argv[])
{
	ifstream instream(BINARY_DIR "/input.txt");

	if (!instream.is_open())
	{
		cerr << "Unable to open input.txt";
		return 1;
	}

	string text;

	getline( instream, text );

	normalize(text);
	reverse(text.begin(), text.end());

	string key;

	ofstream outstream(BINARY_DIR "/output.txt");

	while (!instream.eof())
	{
		getline(instream, key);

		normalize(key);

		const size_t i = text.find(key);

		if (i != string::npos)
		{
			outstream << "YES" << endl;
		}
		else
		{
			outstream << "NO" << endl;
		}
	}

	outstream.close();
	instream.close();
}
