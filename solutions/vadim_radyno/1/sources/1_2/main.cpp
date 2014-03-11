
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <sstream>


using namespace std;

namespace Constants
{
	namespace Paths
	{
		const string input_file = BINARY_DIR "/input.txt";
		const string output_file = BINARY_DIR "/output.txt";
	}

	namespace Results
	{
		const string good = "YES";
		const string bad  = "NO";
	}

	const double round_coefficient = 10000.0;
} 


template<typename T>
T convertString(const string& _str)
{
	T result = 0;

	stringstream change_stream;
	change_stream << _str;
	change_stream >> result;

	return result;
}


class cRoundNumber final
{
public:
	explicit cRoundNumber(const double _number)
		: m_integer_part(0)
		, m_fractional_part(0)
	{
		setNumber(_number);
	}

	void setNumber(const double _number)
	{
		m_integer_part = static_cast<int>(_number);
		double dractional = _number - m_integer_part;
		m_fractional_part = static_cast<int>(dractional * Constants::round_coefficient);
	}

	bool operator==(const cRoundNumber& _number)
	{
		if (   _number.m_integer_part == m_integer_part
			&& _number.m_fractional_part == m_fractional_part)
		{
			return true;
		}

		return false;
	}

private:
	int m_integer_part;
	int m_fractional_part;
};


int main( int argc, char* argv[] )
{
	ifstream input_file( Constants::Paths::input_file);

 	deque<cRoundNumber> passwords;
 	deque<cRoundNumber> codes;

	//read N
	string count_value_str;
	if (!input_file.eof())
	{
		getline(input_file, count_value_str);
	}
	const int count_value = convertString<int>(count_value_str);

	//read codes
	int count_codes = count_value;
	while (count_codes != 0 && !input_file.eof())
	{
		--count_codes;

		string code_str;
		getline(input_file, code_str);

		codes.emplace_back(convertString<double>(code_str));
	}

	//read passwords
	int count_passwords = count_value;
	while (count_passwords != 0 && !input_file.eof())
	{
		--count_passwords;

		string password_str;
		getline(input_file, password_str);

		passwords.emplace_back(convertString<double>(password_str));
	}

	//read next passwords
	while( !input_file.eof() )
	{
		string password_str;
		getline(input_file, password_str);
		passwords.emplace_back(convertString<double>(password_str));
	}

	input_file.close();

	ofstream output_file(Constants::Paths::output_file);	

	for (auto it_password = passwords.begin(); it_password != passwords.end(); ++it_password)
	{
		string result(Constants::Results::bad);
	
		for (auto it_code = codes.begin(); it_code != codes.end(); ++it_code)
		{
			if ((*it_password) == (*it_code))
			{
				result = Constants::Results::good;
			}
		}

		cout << result << endl;
		output_file << result << endl;
	}

	output_file.close();
	return 0;
}
