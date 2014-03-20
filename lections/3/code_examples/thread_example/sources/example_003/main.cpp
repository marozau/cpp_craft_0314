#include <string>
#include <iostream>
#include <string>

#include <boost/thread.hpp>

namespace day_3
{
	typedef std::string type;
	typedef boost::shared_ptr< type > example_ptr;
	static boost::mutex mtx_;

	void f( example_ptr& ptr )
	{
		boost::mutex::scoped_lock lock( mtx_ );
		ptr.reset( new type( "this is new string" ) );
		std::cout << *ptr << std::endl;
	}

	class test
	{
		example_ptr ptr_;

	public:
		explicit test()
		{
			ptr_.reset( new type( "this is new string" ) );
		}
		void process()
		{
			while( true )
				f( ptr_ );
		}
	};
}

int main()
{
    day_3::test t;
    static const size_t thread_size = 6;
    boost::thread_group tg;
    for( size_t i = 0; i < thread_size; ++i )
        tg.create_thread( boost::bind( &day_3::test::process, &t ) );

    tg.join_all();
}

