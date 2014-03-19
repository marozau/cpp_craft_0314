#include <iostream>
#include <cstdlib>
#include <ctime>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>

namespace day_3
{
	class factorial
	{
		boost::recursive_mutex mtx_;
	public:
		size_t process( const size_t n )
		{
			boost::recursive_mutex::scoped_lock lock( mtx_ );
			if ( n == 0 )
				return 1;
			else
				return n * process( n - 1 );
		}
	};
	class multithread
	{
		factorial f_;
	public:
		explicit multithread()
		{
		}
		void process()
		{
			static const size_t module = 20;
			srand ( static_cast< unsigned int >( clock() ) );
			const int random = rand() % module;
			std::cout << random << "! is " << f_.process( random ) << std::endl;
		}
	};
}

int main()
{	
	day_3::multithread mth;
	boost::thread_group thg;
	static const size_t threads_amount = 4;
	for( size_t i = 0; i < threads_amount; ++i )
	{
		thg.create_thread( boost::bind( &day_3::multithread::process, &mth ) );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 5 ) );		
	}

	thg.join_all();
}