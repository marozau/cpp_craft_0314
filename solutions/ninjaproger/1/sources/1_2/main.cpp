#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <math.h>


int main()
{
    
    std::ifstream input_file(SOURCE_DIR "/input.txt");
    std::ofstream output_file(SOURCE_DIR "/output.txt");
    
    if(!input_file.is_open())
        return 1;
    
    std::string n_str;
    std::getline(input_file, n_str);
    
    unsigned long n = 0;
    
    if(n_str.length())
        n = std::stoul(n_str);
    
    std::vector<double> codes_vector;
    std::string code_str;
    
    for (unsigned long i = 0; i < n; i++)
    {
        std::getline(input_file, code_str);
        if(code_str.length())
            codes_vector.push_back(std::stod(code_str));
    }
    
    std::stack<double> passwords_vector;
    std::string password_str;
    
    while (!input_file.eof())
    {
        std::getline(input_file, password_str);
        if(password_str.length())
            passwords_vector.push(std::stod(password_str));
    }
    
    while (!passwords_vector.empty())
    {
        double password = passwords_vector.top();
        
        for(size_t i = 0; i < codes_vector.size(); i++)
        {
            double code = codes_vector.at(i);
            
            if(fabs(password - code) <= 0.0001)
            {
                output_file << "YES\n";
                //std::cout << "YES\n";
                break;
            }
            else if(i == (codes_vector.size()-1))
            {
                output_file << "NO\n";
                //std::cout << "NO\n";
            }
            
            
        }
        
        output_file.flush();
        
        passwords_vector.pop();
    }
    
    input_file.close();
    output_file.close();
    
	return 0;
}
