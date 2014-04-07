#include "small_buffer.h"
#include <boost/unordered_map.hpp>
#include <vector>

void::small_buffer::small_buffer::run()
{

	const unsigned int max_buff_size = 2048;

	typedef boost::unordered_map<boost::uint32_t, boost::uint32_t> def_type_time;//store type and current time for it
	typedef boost::unordered_map<boost::uint32_t, size_t > def_type_buff;//store type and current buffer
	typedef boost::unordered_map<boost::uint32_t, std::vector<int>> def_type_sav_sec;//store type and count of saved messages and seconds
	typedef boost::unordered_map<boost::uint32_t, bool> def_type_if_first;//show if vector doesn't have memory

	std::ifstream in( BINARY_DIR"/input.txt", std::ios_base::binary );
	std::ofstream out( BINARY_DIR"/output.txt", std::ios_base::binary );

	if( (!in.is_open()) || (!out.is_open()) )
		throw std::exception( "Error while opening files" );

	def_type_time type_time;
	def_type_buff type_buff;
	def_type_sav_sec type_sav_sec;
	def_type_if_first type_if_first;

	while( true )
	{

		std::streamoff pos = in.tellg();
		in.get();
		if(in.eof())
			break;
		in.seekg(pos);

		binary_reader::market_message buff_msg( in );

		size_t curr_size = ( sizeof( boost::uint32_t )*3 + sizeof( char )*( buff_msg.len() ) );

		if( !type_if_first[buff_msg.type()] )
		{
			type_sav_sec[buff_msg.type()].reserve(2);
			type_sav_sec[buff_msg.type()].push_back(0);
			type_sav_sec[buff_msg.type()].push_back(0);
			type_time[buff_msg.type()] = 0;
			if( ( buff_msg.time() == 0 ) && ( curr_size <= max_buff_size ) )
				type_sav_sec[buff_msg.type()][1] = 0;
			type_if_first[buff_msg.type()] = 1;
		}

		if( type_time[buff_msg.type()] < buff_msg.time() )
		{
			type_buff[buff_msg.type()] = 0;
			type_time[buff_msg.type()] = buff_msg.time();
			type_sav_sec[buff_msg.type()][1]++;

			if( curr_size <= max_buff_size )
			{
				type_buff[buff_msg.type()] = curr_size;
				type_sav_sec[buff_msg.type()][0]++;
			}
			else
				continue;
		}
		else
		{
			if( (type_buff[buff_msg.type()] += curr_size) <= max_buff_size )
				type_sav_sec[buff_msg.type()][0]++;

			else
				continue;
		}

	}

	for( def_type_sav_sec::iterator iter = type_sav_sec.begin(); iter != type_sav_sec.end(); iter++ )
	{
		boost::uint32_t curr_type = iter->first;
		out.write( reinterpret_cast<char*> (&curr_type), sizeof( boost::uint32_t ) );
		double avrg = ((double)(iter->second[0]))/((double)(iter->second[1]));
		out.write( reinterpret_cast<char*> (&avrg), sizeof( double ) );
	}

	in.close();
	out.close();

}