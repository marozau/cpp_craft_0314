#ifndef reader_h
#define reader_h
#include <string>
#include <fstream>
#include <boost\noncopyable.hpp>
namespace io
{
	class bin_reader:virtual protected boost::noncopyable
	{
		std::ifstream in;
		public:
			bin_reader(const std::string& name);
			~bin_reader();
			template <typename T>
			void read(T &a)
			{
				in.read(reinterpret_cast< char* >( &a ), sizeof( T ) );
			}
			void read(char* a,const size_t length);
			std::string read(const size_t length);
			bool is_open()const;
			bool eof() const;
				
	};

}
#endif 