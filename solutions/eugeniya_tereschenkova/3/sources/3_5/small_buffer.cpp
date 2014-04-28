#include "market_message.h"
#include "small_buffer.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;

bool is_good_type (const boost::uint32_t type, const boost::uint32_t type_min, const boost::uint32_t type_max)
{
	return ((type >= type_min) && (type <= type_max)) ;
} 

string get_infilename(const int file_number)
{
	char id[4];
	sprintf_s( id, 4, "%03d", file_number);
	return  "/input_"+ boost:: lexical_cast<string>(id)+".txt";
}

task3_5::solution::solution( const int files_count ):files_count_(files_count)
{
	if(files_count < 1)
	{
		return;
	}
}

void task3_5::solution::process_file_()
{
  while(true)
  {
    boost::mutex::scoped_lock lock_file_(task3_5::solution::wait_file_);
    if(files_count_ < 1)
    {
      lock_file_.unlock();
      break;
    }
    const string inp_file = BINARY_DIR + get_infilename(files_count_);
    --files_count_;
    lock_file_.unlock();

    ifstream input_file(inp_file.c_str(), ios::binary);    
    if (!input_file.is_open())
    {
      continue;
    }    
    
    try
    {    
      map <boost:: uint32_t, task3_5::struct_type_param> map_type_size;
      while (!input_file.eof())
      {
        binary_reader::market_message mark_mes(input_file);
        if (input_file.eof()) 
          break;
        const boost:: uint32_t type = mark_mes.type();
        if( !is_good_type(type, task3_5::type_min, task3_5::type_max))
          continue;
        
        const boost:: uint32_t time = mark_mes.time();
        const boost:: uint32_t msg_size = mark_mes.msg_size();
        const boost:: uint32_t new_msg_size = msg_size + map_type_size[type].map_time_size[time];
        if (mark_mes.check_msg_size(new_msg_size))
        {
          ++map_type_size[type].count;
          map_type_size[type].map_time_size[time] = new_msg_size;
        }
      }
      
      boost::mutex::scoped_lock lock_out_param_(task3_5::solution::wait_out_param_);
      map <boost:: uint32_t, task3_5::struct_type_param>::iterator iter;
		  for(iter = map_type_size.begin(); iter!=map_type_size.end(); ++iter)
		  {
        const boost:: uint32_t type = (*iter).first;
        map_struct_out_param_[type].count_mes += (*iter).second.count;
        map_struct_out_param_[type].count_sec += static_cast<int>((*iter).second.map_time_size.size());
		  }	
	  }
	  catch(...) 
	  {
		  input_file.close();
		  continue;
	  };

	  input_file.close();
  }
}

void task3_5::solution::start()
{
  boost::thread_group group_threads;
  static const int threads_count = 4;

	for (int i = 0; i < threads_count; ++i)
	{
		group_threads.create_thread( boost::bind( &task3_5::solution::process_file_, this ));
	}
	group_threads.join_all();
  
  if(map_struct_out_param_.size() != 0)
  {
    const string outp_file = BINARY_DIR "/output.txt";
    ofstream output_file(outp_file.c_str(), ios::binary);
    try
    {
      boost::mutex::scoped_lock lock_out_param_(task3_5::solution::wait_out_param_);
      map <boost:: uint32_t, task3_5::struct_out>::iterator iter;
	    for(iter = map_struct_out_param_.begin(); iter!=map_struct_out_param_.end(); ++iter)
	    {
		    const double mean_mes_for_all_time = static_cast<double>((*iter).second.count_mes)/static_cast<double>((*iter).second.count_sec);
		    if(mean_mes_for_all_time !=0)
        {
          const boost:: uint32_t type = (*iter).first;      
			    output_file.write(reinterpret_cast<const char *>(&type), sizeof(boost:: uint32_t));
			    output_file.write(reinterpret_cast<const char *>(&mean_mes_for_all_time), sizeof(double));
        }
	    } 
    }
	  catch(...) 
	  {
      output_file.close();
    }
  }
}
