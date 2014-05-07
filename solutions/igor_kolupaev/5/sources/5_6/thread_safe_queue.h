#ifndef _TASK5_6_THREAD_SAFE_QUEUE_H_
#define _TASK5_6_THREAD_SAFE_QUEUE_H_

#include <cstdlib>
#include <queue>
#include <boost\thread.hpp>

namespace task5_6
{
	template< typename T >
	class thread_safe_queue
	{
		std::queue<T> queue_;

		mutable boost::mutex queue_mutex_;

	public:

		void push( const T& new_element );
		bool pop( T& result );

		bool empty() const;
		size_t size() const;
	};

	template< typename T >
	void thread_safe_queue< T >::push( const T& value )
	{
		boost::mutex::scoped_lock lock( queue_mutex_ );
		queue_.push( value );
	}

	template< typename T >
	bool thread_safe_queue< T >::pop( T& value )
	{
		boost::mutex::scoped_lock lock( queue_mutex_ );

		if( queue_.empty() )
		{
			return false;
		}

		value = queue_.front();
		queue_.pop();

		return true;
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
	{
		boost::mutex::scoped_lock lock( queue_mutex_ );

		return queue_.empty();
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
	{
		boost::mutex::scoped_lock lock( queue_mutex_ );

		return queue_.size();
	}
}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
