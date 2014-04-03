//1
#include <fstream>
#include <string>
#include <stdexcept>
#include <reader.h>
#include <writer.h>
#include <iostream>
#include <boost/noncopyable.hpp>
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
	io::bin_writer& operator<<(io::bin_writer &out,data &obj)
	{
		out.write(obj.type);
		out.write(obj.time);
		out.write(obj.length);
		if ( obj.length )
		out.write(obj.msg,obj.length);
		return out;

	}
class task
{
	io::bin_reader in;
	io::bin_writer out;
	static const unsigned max_type=5u;
	static const unsigned max_difference=2u;
public:
	task()
		: in(BINARY_DIR"/input.txt" ),out(BINARY_DIR"/output.txt")
	{
		if (!in.is_open()) throw(std::logic_error("Can't open Input"));
		if (!out.is_open()) throw(std::logic_error("Can't open Output"));
		
	}


	void solve()
	{
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
