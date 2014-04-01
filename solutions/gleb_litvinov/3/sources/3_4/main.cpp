//1
#include <fstream>
#include <string>
#include <stdexcept>
#include <reader.h>
#include <writer.h>
#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
class task
{
	static const unsigned t_count=4;
	static const unsigned f_count=1000;
	static const std::string pref;
	int file_number;
	static const unsigned max_type=5u;
	static const unsigned max_difference=2u;
	boost::mutex mtx;

	struct data
	{
		unsigned type,time,length;
		char *msg;
		friend io::bin_reader& operator>>(io::bin_reader &in,data &obj);
		friend io::bin_writer& operator<<(io::bin_writer &out,data &obj);
		data():msg(NULL){}
		~data()
		{
			
			delete[] msg;
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


	friend io::bin_writer& operator<<(io::bin_writer &out,data &obj)
	{
		out.write(obj.type);
		out.write(obj.time);
		out.write(obj.length);
		if ( obj.length )
		out.write(obj.msg,obj.length);
		return out;

	}

public:
	task()
	{}

	~task()
	{}

	void start()
	{
		io::bin_writer out;
		file_number=0;
		boost::thread_group t;
		out.open(pref+"output.txt");
			if (!out.is_open())
				throw(std::logic_error("Can't open file"));
		for(int i=0;i<f_count;++i)
			t.create_thread( boost::bind(&task::solve,this));
		t.join_all();
	}

	void solve()
	{
		io::bin_reader in;
		io::bin_writer out;
		{
			char c[4];
			boost::mutex::scoped_lock lock(mtx);
			while(!in.is_open() && file_number<f_count)
			{
				sprintf(c,"%03d",file_number);
				in.open(pref+"input_"+c+".txt");
				file_number++;
			}
			file_number--;
			sprintf(c,"%03d",file_number);
			out.open(pref+"output_"+c+".txt");
			if (!out.is_open())
				throw(std::logic_error("Can't open file"));
			if (!in.is_open())
				throw(std::logic_error("Can't open file"));
		}
		data current_data;
		in>>current_data;
		unsigned T=0;
		while (!in.eof())
		{
			if(current_data.type<max_type)
			{
			if (current_data.time>T)
				T=current_data.time;
			if (T-current_data.time<max_difference)
				out<<current_data;
			}
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
