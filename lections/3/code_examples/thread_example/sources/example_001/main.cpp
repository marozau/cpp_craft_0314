#include <string>
#include <iostream>
#include <boost/thread.hpp>

namespace day_3
{
	void f1()
	{
		std::cout << "f1" << std::endl;
	}

	class help
	{
	public:
		void f2()
		{
			std::cout << "f2" << std::endl;
		}
	};
}

int main()
{
	boost::thread slave_thread( &day_3::f1 );
	boost::this_thread::sleep(boost::posix_time::microseconds( 100 ) );
	std::cout << "slave thread was created" << std::endl;

    day_3::help h;
	static const size_t threads_count = 4;
	boost::thread_group group_of_slave_threads;
	for( size_t i = 0; i < threads_count; ++i )
        group_of_slave_threads.create_thread( boost::bind( &day_3::help::f2, &h ) );
    slave_thread.join();
    group_of_slave_threads.join_all();
}

