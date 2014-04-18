#include <set>

#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/chrono/chrono_io.hpp>

#include <ts_queue.h>

boost::mutex mutex;
std::set< size_t > working_threads_;

class task
{
public:
	void operator()()
	{
		boost::this_thread::sleep_for( boost::chrono::milliseconds( 1000 ) );
	}
};

typedef system_utilities::common::ts_queue< task > task_queue;

void processor( const size_t index, task_queue& queue )
{
	while (true)
	{
		boost::scoped_ptr< task > task_ptr( queue.wait_pop() );
		if ( !task_ptr )
			break;
		(*task_ptr)();
		{
			boost::mutex::scoped_lock lock( mutex );
			if ( working_threads_.find( index ) == working_threads_.end() )
				break;
		}
	}
}

int main()
{

	system_utilities::common::ts_queue< task > task_queue;

	boost::thread_group thread_group;

	for( size_t i = 0 ; i < 4 ; ++i )
	{
		boost::mutex::scoped_lock lock( mutex );
		working_threads_.insert( i );
		thread_group.create_thread( boost::bind( &processor, i, boost::ref( task_queue ) ) );
	}

	boost::chrono::system_clock::time_point s1 = boost::chrono::system_clock::now();

	for( size_t i = 0 ; i < 12 ; ++i )
	{
		task* task_ptr = new task;
		if ( !task_queue.push( task_ptr ) )
		{
			delete task_ptr;
			break;
		}
	}

	task_queue.wait();
	boost::chrono::system_clock::time_point s2 = boost::chrono::system_clock::now();

	{
		boost::mutex::scoped_lock lock( mutex );
		working_threads_.erase( working_threads_.find( 2 ) );
		working_threads_.erase( working_threads_.find( 0 ) );
	}

	for( size_t i = 0 ; i < 4 ; ++i )
	{
		task* task_ptr = new task;
		if ( !task_queue.push( task_ptr ) )
		{
			delete task_ptr;
			break;
		}
	}
	boost::chrono::system_clock::time_point s3 = boost::chrono::system_clock::now();

	for( size_t i = 0 ; i < 12 ; ++i )
	{
		task* task_ptr = new task;
		if ( !task_queue.push( task_ptr ) )
		{
			delete task_ptr;
			break;
		}
	}

	task_queue.wait();
	boost::chrono::system_clock::time_point s4 = boost::chrono::system_clock::now();
	task_queue.stop();

	thread_group.join_all();

//	std::cout << "01 " << s1 << std::endl;
//	std::cout << "02 " << s2 << std::endl;
//	std::cout << "03 " << s3 << std::endl;
//	std::cout << "04 " << s4 << std::endl;

	std::cout << "d01 " << s2 - s1 << std::endl;
	std::cout << "d02 " << s4 - s3 << std::endl;

}
