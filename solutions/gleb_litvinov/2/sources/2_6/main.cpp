//3
#include <fstream>
#include <string>
#include <stdexcept>
#include <reader.h>
#include <writer.h>
#include <iostream>



class task
{
public:
	struct data
	{
		unsigned date,volume;
		double f1, t1, f2, f3, f4,price,vwap;
		char *name;
		friend io::bin_reader& operator>>(io::bin_reader &in,data &obj);
		friend io::bin_writer& operator<<(io::bin_writer &out,data &obj);
	};
	data current_data;
	io::bin_reader in;
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
		in>>current_data;
		long long T=0;
		while (!in.eof())
		{
			
			out<<current_data;
			in>>current_data;
		}


	}
	

};


	io::bin_reader& operator>>(io::bin_reader &in,task::data &obj)
	{
		obj.name=new char[8];
		in.read(obj.name,8);
		in.read(obj.date);
		in.read(obj.price);
		in.read(obj.vwap);
		in.read(obj.volume);
		in.read(obj.f1);
		in.read(obj.t1);
		in.read(obj.f2);
		in.read(obj.f3);
		in.read(obj.f4);
		return in;

	}
	io::bin_writer& operator<<(io::bin_writer &out,task::data &obj)
	{
		out.write(obj.name,9);
		out.write(obj.date);
		out.write(obj.price);
		out.write(obj.volume);
		out.write(obj.f2);
		return out;

	}
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

