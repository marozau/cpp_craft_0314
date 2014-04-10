#include "test_registrator.h"

#include <thread_safe_queue.h>

#include <stdexcept>

#include <boost/thread.hpp>

namespace task5_6
{
	namespace tests_
	{
		namespace detail
		{
			class thread_safe_queue_many_thread_helper
			{
				thread_safe_queue< int > queue;

				boost::mutex protect_size_;
				size_t writen_size_;
				size_t readed_size_;

			public:
				explicit thread_safe_queue_many_thread_helper( const size_t write_threads_amount, const size_t read_threads_amount );
				void write_thread();
				void read_thread();
			};
		}
	}
}

//
task5_6::tests_::detail::thread_safe_queue_many_thread_helper::thread_safe_queue_many_thread_helper( const size_t write_threads_amount, const size_t read_threads_amount )
	: writen_size_( 0ul )
	, readed_size_( 0ul )
{
	boost::thread_group writers;
	boost::thread_group readers;

	for( size_t i = 0 ; i < write_threads_amount ; ++ i )
		writers.create_thread( boost::bind( &thread_safe_queue_many_thread_helper::write_thread, this ) );

	for( size_t i = 0 ; i < read_threads_amount ; ++ i )
		readers.create_thread( boost::bind( &thread_safe_queue_many_thread_helper::read_thread, this ) );

	writers.join_all();
	readers.join_all();

	size_t amount = 0;
	while ( !queue.empty() )
	{
		int data;
		if ( queue.pop( data ) )
			++amount;
	}

	BOOST_CHECK_EQUAL( writen_size_, readed_size_ + amount );
}
void task5_6::tests_::detail::thread_safe_queue_many_thread_helper::write_thread()
{
	const int size = rand() % 1000 + 1000;
	for( int i = 0 ; i < size ; ++i )
		queue.push( i );

	boost::mutex::scoped_lock increase_size( protect_size_ );
	writen_size_ += size;
}
void task5_6::tests_::detail::thread_safe_queue_many_thread_helper::read_thread()
{
	size_t amount = 0;
	while ( !queue.empty() )
	{
		int data;
		if ( queue.pop( data ) )
			++amount;
	}
	boost::mutex::scoped_lock increase_size( protect_size_ );
	readed_size_ += amount;
}


void task5_6::tests_::thread_safe_queue_tests()
{
	{
		thread_safe_queue< int > tsq;
		BOOST_CHECK_EQUAL( tsq.size() , 0ul );
		BOOST_CHECK_EQUAL( tsq.empty() , true );
		tsq.push( 45 );
		BOOST_CHECK_EQUAL( tsq.size() , 1ul );
		BOOST_CHECK_EQUAL( tsq.empty() , false );
	}
	{
		thread_safe_queue< int > tsq;
		tsq.push( 54 );
		BOOST_CHECK_EQUAL( tsq.size() , 1ul );
		BOOST_CHECK_EQUAL( tsq.empty() , false );

		int res;
		BOOST_CHECK_EQUAL( tsq.pop( res ), true );
		BOOST_CHECK_EQUAL( res, 54 );
		BOOST_CHECK_EQUAL( tsq.size() , 0ul );
		BOOST_CHECK_EQUAL( tsq.empty() , true );

		res = 4265624;
		BOOST_CHECK_EQUAL( tsq.pop( res ), false );
		BOOST_CHECK_EQUAL( res, 4265624 );
	}
}

void task5_6::tests_::thread_safe_queue_many_thread_tests()
{
	detail::thread_safe_queue_many_thread_helper tsqmth( 4ul, 7ul );
}

void task5_6::tests_::thread_safe_queue_a_lot_of_thread_tests()
{
	detail::thread_safe_queue_many_thread_helper tsqmth( 40ul, 70ul );
}

