#ifndef writer_h
#define writer_h
#include <string>
#include <fstream>
#include <boost\noncopyable.hpp>
namespace io
{
	class bin_writer:virtual protected boost::noncopyable
	{
		std::ofstream out;
		public:
			bin_writer(std::string name);
			~bin_writer();
			template <typename T>
			void write(T &a)
			{
				out.write(reinterpret_cast< char* >( &a ), sizeof( T ) );
			}
			void write(char* a,const size_t length);
			void write(std::string a);
			bool is_open();
		
				
	};

}
#endif 