//2
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>
#include <set>
#include <reader.h>
#include <writer.h>
#include<iostream>
#include <boost/thread.hpp>
#include <boost/ref.hpp>

typedef  std::map<unsigned,int> mmap;

class task
{
	int file_number;
	boost::mutex mtx;
	static const unsigned t_count=4;
	static const unsigned f_count=1000;
	static const std::string pref;
	static const size_t max_memory=2048ul;
	mmap met,times;
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

	friend io::bin_reader& operator>>(io::bin_reader &in,data &obj)
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
	data current_data;
public:
	task()
	{}

	void start()
	{
			io::bin_writer out;
		file_number=0;
		boost::thread_group t;
		out.open(pref+"output.txt");
			if (!out.is_open())
				throw(std::logic_error("Can't open file"));
		file_number=0;
		boost::thread_group t;
		for(int i=0;i<f_count;++i)
			t.create_thread( boost::bind(&task::solve,this));
		t.join_all();
		for (mmap::iterator it=met.begin();it!=met.end();it++)
		{
			unsigned i=it->first;
			out.write(i);
			const double temp=double(it->second)/times[it->first];
			out.write(temp);
		}
	}

	void solve()
	{
		io::bin_reader in;
		{
			char c[4];
			boost::mutex::scoped_lock lock(mtx);
			while(!in.is_open() && file_number<f_count)
			{
				sprintf(c,"%03d",file_number);
				in.open(pref+"input_"+c+".txt");
				file_number++;
			}
			if (!in.is_open())
				throw(std::logic_error("Can't open file"));
		}
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
					{
						boost::mutex::scoped_lock lock(mtx);
						times[current_data.type]++;
					}
					last.insert(current_data.type);
					{
						boost::mutex::scoped_lock lock(mtx);
						met[current_data.type]++;
					}
				}
				curr_time=current_data.time;
				in>>current_data;
				continue;
			}
			if (current_data.get_size()+size[current_data.type]<=max_memory)
			{
				{
					boost::mutex::scoped_lock lock(mtx);
					met[current_data.type]++;
				}
				size[current_data.type]+=current_data.get_size();
			}			
			curr_time=current_data.time;
			in>>current_data;
			
		}
	}
};

const std::string task::pref=BINARY_DIR"/";
	
void main()
{
	try
	{	
		task realization;
		realization.start();
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

