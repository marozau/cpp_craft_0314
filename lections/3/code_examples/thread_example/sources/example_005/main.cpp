#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>

namespace day_3
{
	class condition_example : protected virtual boost::noncopyable
	{
		boost::thread_group threads_;		
		bool stopping_;			

		boost::condition wait_condition_;
		mutable boost::mutex wait_;
		volatile size_t working_threads_;

	public:
		explicit condition_example( const size_t thread_amount )
			: stopping_( false )
			, working_threads_( 0 )
		{
			for( size_t i = 0 ; i < thread_amount ; ++i )
				threads_.create_thread( boost::bind( &condition_example::processing, this ) );
		}
		~condition_example()
		{
			stop();

			threads_.join_all();
		}
		void wait()
		{
			boost::mutex::scoped_lock lock( wait_ );
			while ( working_threads_ != 0 )
				wait_condition_.wait( lock );
		}
		void stop()
		{			
			stopping_ = true;
			wait();
		}
		void processing()
		{
			while ( !stopping_ )
			{
				{
					boost::mutex::scoped_lock lock( wait_ );
					++working_threads_;
				}
				// multithread processing
				// for example: file reading and filtering				
				{
					boost::mutex::scoped_lock lock( wait_ );
					--working_threads_;
					if ( working_threads_ == 0 )
						wait_condition_.notify_all();
				}
			}
		}
	};
}

int main()
{
	day_3::condition_example example( 4 );
	boost::this_thread::sleep( boost::posix_time::milliseconds( 4000 ) );
}