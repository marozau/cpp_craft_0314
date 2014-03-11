#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <functional>


class task
{
	std::ifstream in;
	std::ofstream out;

public:
	task()
	{   
		const std::string inp=BINARY_DIR"/Input.txt",
		outp=BINARY_DIR"/Output.txt";
		in.open(inp);
		if (!in.is_open()) throw(std::logic_error("Can't open file "+inp));
		out.open(outp);
		if (!out.is_open()) throw(std::logic_error("Can't open file "+outp));
	}

	struct pred : std::unary_function<char,bool>
	{
		bool operator() (const char c) const
		{
			return (c==' '||c=='\\'||c=='-');
		}

	};

	void solve()
	{
		std::string first,temp;			
		while( !in.eof() )
		{   
			std::stringstream stream;
			std::getline( in, temp );
			temp.erase(remove_if(temp.begin(),temp.end(),pred()),temp.end());
			for(unsigned i=0;i<temp.size();++i)
				temp[i]=tolower(temp[i]);
			if (first.size()==0)
				first=temp;
			else
			{
				std::reverse(temp.begin(),temp.end());
				if (first.find(temp)!=std::string::npos) 
					out<<"YES"<<"\n";
				else
					out<<"NO"<<"\n";
			}
			
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
