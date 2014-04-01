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

typedef  std::map<unsigned,int> mmap;
struct data
	{
		unsigned type,time,length;
		char *msg;
		friend io::bin_reader& operator>>(io::bin_reader &in,data &obj);
		size_t get_size()
		{
			return sizeof(unsigned)*3+length;
		}
		data():msg(NULL){}
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
		if ( obj.length )
		{
			obj.msg=new char[obj.length+1];
			in.read(obj.msg,obj.length);
		}
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
		: in(BINARY_DIR"/input.txt" ),out(BINARY_DIR"/output.txt")
	{   
		if (!in.is_open()) throw(std::logic_error("Can't open file"));
		if (!out.is_open()) throw(std::logic_error("Can't open file "));
		
	}


	void solve()
	{   
		mmap met,times;
		std::set<unsigned> last;
		std::map<unsigned,size_t> size;
		in>>current_data;
		unsigned curr_time=0;
		while (!in.eof())
		{
			if ( current_data.time != curr_time || last.find(current_data.type) == last.end() )
			{
				if (current_data.time!=curr_time)
				last.clear();
				if (current_data.get_size()<=max_memory)
				{
					size[current_data.type]=current_data.get_size();
					if (last.find(current_data.type)==last.end())
					times[current_data.type]++;
					last.insert(current_data.type);					
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
		for (mmap::iterator it=met.begin();it!=met.end();it++)
		{
			unsigned i=it->first;
			out.write(i);
			const double temp=static_cast<double>(it->second)/times[it->first];
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
	catch(std::exception )
	{
		std::cout<<"Unknown error";
	}
	catch( ... )
	{
		std::cout<<"Unknown error";
	}
	

}

