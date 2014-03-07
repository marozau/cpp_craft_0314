#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <vector>

//std::lower_bound
class task
{
	std::ifstream in;
	std::ofstream out;

public:
	task()
	{   const std::string inp="Input.txt",
	    outp="Output.txt";
		in.open(inp);
		if (!in.is_open()) throw(std::logic_error("Can't open file"+inp));
		out.open(outp);
		if (!out.is_open()) throw(std::logic_error("Can't open file"+outp));
	}


	void solve()
	{   
		std::vector<double> numbers,keys;
		int n;
		const double eps=1e-4;
		double temp;
		in>>n;
		for(int i=0;i<n;++i)
		{
			in>>temp;
			numbers.push_back(temp);
		}
		bool check=false;
		std::sort(numbers.begin(),numbers.end());
		while( !in.eof() )
		{   
			check=false;
			in>>temp;
			std::vector<double>::iterator it=std::lower_bound(numbers.begin(),numbers.end(),temp);
			if (it!=numbers.end())
			{
				if (fabs(temp-*it)<=eps)
					check=true;
				
			}
			if (it!=numbers.begin())
			{
				--it;
				if (fabs(temp-*it)<=eps)
					check=true;
				
			}
			if (check)
				out<<"YES"<<"\n";
			else
				out<<"NO"<<"\n";
		}
		
	}
	~task()	
	{
		in.close();
		out.close();
	}

};

int main()

{  
    try
    {
		task realization;
		realization.solve();
    }
    catch(const std::logic_error& message)
	{
		std::cout<<message.what()<<"\n";
	}
	return 0;
}
