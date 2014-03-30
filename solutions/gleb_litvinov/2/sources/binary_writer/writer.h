#ifndef writer_h
#define writer_h
#include <string>
#include <fstream>
#include <boost\noncopyable.hpp>
namespace io
{
	class bin_writer:virtual protected boost::noncopyable
	{
		mutable std::ofstream out;
		public:
			bin_writer(std::string name);
			~bin_writer();
			template <typename T>
			void write(T &a)const
			{
				out.write(reinterpret_cast< char* >( const_cast< T* >( &a ) ), sizeof( T ) );
			}
			void write(const char* const a,const size_t length)const;
			bool is_open()const ;
		
				
	};

}
#endif 