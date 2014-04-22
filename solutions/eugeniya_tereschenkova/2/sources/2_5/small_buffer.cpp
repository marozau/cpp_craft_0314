#include "market_message.h"
#include <iostream>
#include <map>
using namespace std;

struct struct_type_param
{
  struct_type_param()
  {
    count = 0;
  };
	int count;
	map < boost:: uint32_t, boost:: uint32_t> map_time_size;
};

bool is_good_type (const boost::uint32_t type, const boost::uint32_t type_min, const boost::uint32_t type_max)
{
	return ((type >= type_min) && (type <= type_max)) ;
} 

int main()
{
	static const char* inp_file = BINARY_DIR "/input.txt";
	ifstream input_file(inp_file, ios::binary);

	if (!input_file.is_open())
	{
		cout << "Could not open input file" << endl;
		return 1;
	}

	static const char* outp_file = BINARY_DIR "/output.txt";
	ofstream output_file(outp_file, ios::binary);

	static const boost::uint32_t type_min = 0u;
	static const boost::uint32_t type_max = 100000u;
  
	try
	{    
		map <boost:: uint32_t, struct_type_param> map_type_size;
		while (!input_file.eof())
		{
			binary_reader::market_message mark_mes(input_file);
			if (input_file.eof()) 
				break;
			const boost:: uint32_t type = mark_mes.type();
			if( !is_good_type(type, type_min, type_max))
				continue;
			
			const boost:: uint32_t time = mark_mes.time();
			const boost:: uint32_t msg_size = mark_mes.msg_size();
			boost:: uint32_t new_msg_size = msg_size + map_type_size[type].map_time_size[time];
			if (mark_mes.check_msg_size(new_msg_size))
			{
				++map_type_size[type].count;
				map_type_size[type].map_time_size[time] = new_msg_size;
			}
		}
      
		map <boost:: uint32_t, struct_type_param>::iterator iter;
		for(iter = map_type_size.begin(); iter!=map_type_size.end(); ++iter)
		{
			const boost:: uint32_t type = (*iter).first;      
			output_file.write(reinterpret_cast<const char *>(&type), sizeof(boost:: uint32_t));
			const double sec_count = static_cast<double>((*iter).second.map_time_size.size());
			const double mean_mes_for_all_time = static_cast<double>((*iter).second.count)/sec_count;
			output_file.write(reinterpret_cast<const char *>(&mean_mes_for_all_time), sizeof(double));
		}	
	}
	catch(...) 
	{
		input_file.close();
		output_file.close();
		return 1;
	};

	input_file.close();
	output_file.close();
	return 0;
}
