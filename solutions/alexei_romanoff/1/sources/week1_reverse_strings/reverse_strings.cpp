#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cctype>
#include <locale>
#include <set>
#include <iomanip>

static const wchar_t bad_chars_array[] = {L' ', L'-', L'\\', L'/'};
static const std::set<wchar_t> bad_chars_set(bad_chars_array, bad_chars_array + sizeof(bad_chars_array)/sizeof(wchar_t));

bool is_bad_char(wchar_t c) {
    bool is_bad_not_found = bad_chars_set.find(c) == bad_chars_set.end();
    return !is_bad_not_found;
}


std::wstring & transform_string(std::wstring &text, std::locale &my_locale) {
    std::wstring chars = L" -/\\";
    text.erase(std::remove_if(text.begin(), text.end(), is_bad_char), text.end());

    std::wstring::iterator it;
    for(it=text.begin(); it != text.end(); ++it) {
        *it = std::tolower(*it, my_locale);
    }

    return text;
}


int main(int argc, char **argv) {
    std::locale my_locale("");
    std::wifstream input;
    std::wofstream output;

    input.imbue(my_locale);
    output.imbue(my_locale);

    //some scaffolds
    //std::cerr << "DEBUG: SOURCE_DIR is " << SOURCE_DIR << "\n";
    //std::cerr << "DEBUG: BINARY_DIR is " << BINARY_DIR << "\n";

    //input.txt file is encoded in UTF-8 encoding
    //if your locale is UTF-8 bases everything would be OK
    //but in other case you need to encode input.txt into some other
    //encoding, e.g. CP1251. 
    //Yeah, yeah, windows user, this comment is for you:)
    input.open(BINARY_DIR "/input.txt", std::ios::binary);
    output.open(BINARY_DIR "/output.txt", std::ios::binary);
    if (not input.is_open()) {
        std::cerr << "Unable to open the input file. Reason: " << 
                      strerror(errno) << "\n";
        return 1;
    }
    if (not output.is_open()) {
        std::cerr << "Unable to open the output file. Reason: " << 
                      strerror(errno) << "\n";
        return 1;
    }

    std::wstring text;
    std::wstring line;

    std::getline(input, text);

    text = transform_string(text, my_locale);

    //output << text << L'\n';
    std::wstring revesed_text(text.rbegin(), text.rend());

    while ( std::getline(input, line) ) {
        line = transform_string(line, my_locale);
        if (revesed_text.find(line) == std::string::npos) {
            output << "NO\n";
        } else {
            output << "YES\n";
        }

        //output << line << L'\n';
    }

    input.close();
    output.close();


    return 0;
}
