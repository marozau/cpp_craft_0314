#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

void str_remove_char(std::string *str,const char ch)
{
    std::size_t ch_pos = str->find(ch);
    while(ch_pos!=std::string::npos)
    {
        str->erase(ch_pos,1);
        ch_pos = str->find(ch);
    }
}

void str_remove_chars(std::string *str,const std::string str_to_rem)
{
    for(int i = 0; i < str_to_rem.length(); i++)
        str_remove_char(str, str_to_rem[i]);
}





int main()
{
    std::ifstream input_file(SOURCE_DIR "/input.txt");
    std::ofstream output_file(SOURCE_DIR "/output.txt");
    
    if(!input_file.is_open())
        return 1;
    
    std::string text;
    std::getline(input_file, text);
    
    if(!text.length())
    {
        std::cout << "Empty file!\n";
        return 1;
    }
    
    std::transform(text.begin(), text.end(),text.begin(), ::tolower);
    
    //std::cout << text << std::endl;
    str_remove_chars(&text, std::string(" \\-"));
    //std::cout << text << std::endl << std::endl;
    
    std::string keys;
    char delimeters[] = " ";
    
    while(!input_file.eof())
    {
        std::getline(input_file, keys);
        std::transform(keys.begin(), keys.end(),keys.begin(), ::tolower);
        
        std::size_t key_start_pos = 0;
        std::size_t next_key_start_pos = keys.find_first_of(delimeters);
        
        if(next_key_start_pos==std::string::npos)
            break;
        
        while(1)
        {
            std::size_t key_len = next_key_start_pos - key_start_pos;
            
            if(key_len)
            {
                std::string key = keys.substr(key_start_pos,key_len);
                std::string reversed_key = key;
                std::reverse(reversed_key.begin(), reversed_key.end());

                std::size_t found_pos = text.find(reversed_key);
                
                if(found_pos!=std::string::npos)
                {
                    output_file << "YES\n";
                    //std::cout << key << " " << reversed_key << " ["<< found_pos << "]" << " YES\n";
                }
                else
                {
                    output_file << "NO\n";
                    //std::cout << key << " " << reversed_key << " ["<< found_pos << "]" << " NO\n";
                }
                
                output_file.flush();
            }
            
            if(next_key_start_pos == std::string::npos)
                break;
            
            key_start_pos = next_key_start_pos+1;
            next_key_start_pos = keys.find_first_of(delimeters,key_start_pos);
        }
        
    }
    
    input_file.close();
    output_file.close();
    
	return 0;
}
