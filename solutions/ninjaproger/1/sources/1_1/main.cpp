#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

void str_remove_chars(std::string &str,const std::string &str_to_rem)
{
    for(int i = 0; i < str_to_rem.length(); i++)
        str.erase(std::remove(str.begin(),str.end(),str_to_rem[i]), str.end());
}

int main()
{
    std::ifstream in_file(BINARY_DIR "/input.txt");
    std::ofstream out_file(BINARY_DIR "/output.txt");
    
    if(!in_file.is_open()||!out_file.is_open())
    {
        std::cout << "Couldn't open files!\n";
        return 1;
    }
    
    std::string text;
    std::getline(in_file, text);
    
    if(!text.length())
    {
        std::cout << "Empty input file!\n";
        return 1;
    }
    
    std::transform(text.begin(), text.end(),text.begin(),::tolower);
    str_remove_chars(text, std::string(" \\-"));
    
    std::string key;
    
    while(!std::getline(in_file, key).eof())
    {
        std::transform(key.begin(), key.end(),key.begin(),::tolower);
        str_remove_chars(key,std::string(" \\-"));
        std::reverse(key.begin(), key.end());
        std::size_t found_pos = text.find(key);
                
        if(found_pos!=std::string::npos)
            out_file << "YES\n";
        else
            out_file << "NO\n";
        
        out_file.flush();
        
    }
    
    in_file.close();
    out_file.close();
    
	return 0;
}
