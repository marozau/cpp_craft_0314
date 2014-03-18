//2
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>
#include <set>
#include <reader.h>
#include <writer.h>
#include<iostream>

#include <boost/ref.hpp>


struct data
	{
		unsigned type,time,length;
		char *msg;
		friend io::bin_reader& operator>>(io::bin_reader &in,data &obj);
		size_t get_size()
		{
			return sizeof(int)*3+length;
		}
		~data()
		{
			delete []msg;
		}
	};	
io::bin_reader& operator>>(io::bin_reader &in,data &obj)
	{
		in.read(obj.type);
		in.read(obj.time);
		in.read(obj.length);
		obj.msg=new char[obj.length];
		in.read(obj.msg,obj.length);
		return in;

	}
class task
{

	data current_data;
	io::bin_reader in;
	static const size_t max_memory=2048ul;
	io::bin_writer out;
public:
	task()
		: in("input.txt" ),out("output.txt")
	{   
		if (!in.is_open()) throw(std::logic_error("Can't open file"));
		if (!out.is_open()) throw(std::logic_error("Can't open file "));
		
	}


	void solve()
	{   
		std::map<unsigned,int> met,times;
		std::set<unsigned> last;
		std::map<unsigned,size_t> size;
		unsigned curr_memory=0;
		in>>current_data;
		unsigned curr_time=0;
		while (!in.eof())
		{
			if (current_data.time!=curr_time||last.find(current_data.type)!=last.end())
			{
				if (current_data.time==curr_time)
				last.clear();
				if (current_data.get_size()<=max_memory)
				{
					size[current_data.type]=current_data.get_size();
					last.insert(current_data.type);
					times[current_data.type]++;
					met[current_data.type]++;
				}
				curr_time=current_data.time;
			    in>>current_data;
				continue;
			}
			if (current_data.get_size()+size[current_data.type]<=max_memory)
			{
				met[current_data.type]++;
				size[current_data.type]+=current_data.get_size();

			}
			
			curr_time=current_data.time;
			in>>current_data;
		}
		for (std::map<unsigned,int>::iterator it=met.begin();it!=met.end();it++)
		{
			size_t i=it->first;
			out.write(i);
			double temp=double(it->second)/times[it->first];
			out.write(temp);
		}

	}
	

};


	
void main()
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
	

}
