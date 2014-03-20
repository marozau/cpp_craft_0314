#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <math.h>


int main()
{
    
    std::ifstream in_file(BINARY_DIR "/input.txt");
    std::ofstream out_file(BINARY_DIR "/output.txt");
    
    if(!in_file.is_open()||!out_file.is_open())
    {
        std::cout << "Couldn't open files!\n";
        return 1;
    }
    size_t n = 0;
    in_file >> n;
    std::vector<double> codes_vector;

    double code = 0.0;
    
    for (unsigned long i = 0; i < n; i++)
    {
        in_file >> code;
        codes_vector.push_back(code);
    }
    
    std::queue<double> passwords_queue;
    
    double pass = 0.0;
    
    while (!in_file.eof())
    {
        in_file >> pass;
        passwords_queue.push(pass);
    }
    
    while (!passwords_queue.empty())
    {
        for(size_t i = 0; i < codes_vector.size(); i++)
        {
            if(fabs(passwords_queue.front() - codes_vector.at(i)) <= 0.0001)
            {
                out_file << "YES\n";
                break;
            }
            else if(i == (codes_vector.size()-1))
            {
                out_file << "NO\n";
            }
        }
        
        out_file.flush();
        passwords_queue.pop();
    }
    
    in_file.close();
    out_file.close();
    
	return 0;
}
