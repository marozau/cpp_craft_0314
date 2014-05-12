#include "property.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace config
{ 
	reader::reader(const string& filename) : 
		opened_(false),
		trade_thread_size_(0), quote_thread_size_(0), 
		trade_ports_amount_(0), quote_ports_amount_(0)
	{
		ifstream in_filename(filename.c_str());
		if(!in_filename.is_open())
		{
			std::cerr << "Error: " << "Cann't open config file: " 
				<< std::endl << filename << std::endl << std::endl;
			return;
		}
		opened_ = true;

		stringstream ss;
		string line;
		getline(in_filename, line);
		ss.str(line);
		ss >> trade_thread_size_;

		getline(in_filename, line);
		ss.clear();
		ss.str(line); 
		ss >> quote_thread_size_; 

		parse_(in_filename, trades_, trade_ports_amount_);
		parse_(in_filename, quotes_, quote_ports_amount_);

		in_filename.close();
	} 

	void reader::parse_(ifstream &in_ifstream, cont_addr_port_& v, size_t& count)
	{
		string line;
		getline(in_ifstream, line);
		stringstream ss;
		ss.clear();
		ss.str(line); 
		ss >> count;

		for(size_t i = 0; i < count; ++i)
		{
			getline(in_ifstream, line);
			ss.clear();
			ss.str(line);
			string addr;
			ss >> addr;

			unsigned short port;
			ss >> port;
			v.push_back(make_pair(addr, port));
		}
	}

	const bool reader::opened() const
	{
		return opened_;
	} 

	const size_t reader::trade_thread_size() const
	{
		return trade_thread_size_;
	}
	const size_t reader::quote_thread_size() const
	{
		return quote_thread_size_;
	}

	const size_t reader::trade_ports_amount() const
	{
		return trade_ports_amount_;
	}
	const size_t reader::quote_ports_amount() const
	{
		return quote_ports_amount_;
	}
	const reader::cont_addr_port_& reader::trades() const
	{
		return trades_;
	}
	const reader::cont_addr_port_& reader::quotes() const
	{
		return quotes_;
	}
}
