#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <xutility>
#include <xlocale>

using namespace std;

namespace Constants
{
    namespace Paths
    {
        const string input_file = SOURCE_DIR "/sources/1_1/input.txt";
        const string output_file = SOURCE_DIR "/sources/1_1/output.txt";
    }

    const string ignore_simbols = " -\\";

    namespace Results
    {
        const string good = "YES";
        const string bad  = "NO";
    }
}


bool isIgnoreSimbol(const string& _simbol)
{
    return (Constants::ignore_simbols.npos != Constants::ignore_simbols.find(_simbol));
}


void removeIgnoreSimbols(string& _str)
{
    for (string::const_iterator it = Constants::ignore_simbols.cbegin(); it != Constants::ignore_simbols.cend(); ++it)
    {
        _str.erase(remove(_str.begin(), _str.end(), (*it)), _str.end());
    }
}


string revertString(const string& _str)
{
    string revert_str;
    revert_str.reserve(_str.size());

    for (auto it = _str.crbegin(); it != _str.crend(); ++it)
    {
        revert_str.push_back(*it);
    }

    return move(revert_str);
}


bool isValidKeyForText(const string& _key, const string& _text)
{
    const string& revert_key = revertString(_key);

    const size_t pos_revert_key = _text.find(revert_key);
    if (pos_revert_key != _text.npos)
    {
        return true;
    }

    return false;
}


void upperCase(string& _text) {
    for(string::iterator it = _text.begin(); it != _text.end(); ++it)
    {
        (*it) = toupper(*it);
    }
}


int main( int argc, char* argv[] )
{
    locale loc("Russian_Russia");

    ifstream input_file( Constants::Paths::input_file );

    if ( !input_file.eof() )
    {
        string first_line;
        getline( input_file, first_line );

        removeIgnoreSimbols(first_line);
        upperCase(first_line);

        ofstream output_file(Constants::Paths::output_file);

        while (!input_file.eof())
        {
            string key_value;
            std::getline( input_file, key_value );

            removeIgnoreSimbols(key_value);
            upperCase(key_value);

            const string& valid_key = isValidKeyForText(key_value, first_line)  ? Constants::Results::good
                                                                                : Constants::Results::bad;
            output_file << valid_key << endl;
            cout << valid_key << endl;
        }
        output_file.close();
    }

    input_file.close();
}
