#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <boost/thread.hpp>

namespace day_3
{
	class ts_search
	{
		const int i_;
		int last_i_;

		boost::mutex last_i_protector_;

	public:
		explicit ts_search( const int i )
			: i_( i )
			, last_i_( 0 )
		{
		}
		const bool is_i( const int i )
		{
			bool result = false;
			if ( i_ == i )
			{
				std::cout << "found i;" << std::endl;
				result = true;
			}
			{
				boost::mutex::scoped_lock lock( last_i_protector_ );
				last_i_ = i;
			}
			return result;
		}
	};

	class test
	{
		ts_search search_;
		const int module_;
		boost::thread_group tg_;

	public:
		explicit test( const int module, const int i, const size_t thread_size )
			:search_( i )
			, module_( module )
		{

			for( size_t i = 0; i < thread_size; ++i )
			{
				tg_.create_thread( boost::bind( &test::generate_i, this ));
				boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );
			}

			tg_.join_all();
		}
		void generate_i()
		{
			size_t i = 0;
			std::srand ( static_cast< unsigned int >( clock() ) );
			while( !search_.is_i( std::rand() % module_ ) )
			{
				++i;
			}
			std::cout << "iterations: " << i << std::endl;
		}
	};
}


int main()
{
    static const int module = 10000;
    static const size_t thread_size = 4;
    day_3::test t( module, 6059, thread_size );
}

