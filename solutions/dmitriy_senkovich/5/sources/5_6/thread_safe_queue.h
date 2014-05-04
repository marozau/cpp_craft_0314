#ifndef _TASK5_6_THREAD_SAFE_QUEUE_H_
#define _TASK5_6_THREAD_SAFE_QUEUE_H_

#include <cstdlib>
#include <queue>
#include <boost/thread.hpp>

namespace task5_6
{
	template< typename T >
	class thread_safe_queue
	{
		std::queue< T > data_;
		mutable boost::mutex lock_access_;

	public:
		explicit thread_safe_queue();
		~thread_safe_queue();

		void push( const T& );
		bool pop( T& );

		bool empty() const;
		size_t size() const;
	};

	template< typename T >
	thread_safe_queue< T >::thread_safe_queue()
	{
	}

	template< typename T >
	thread_safe_queue< T >::~thread_safe_queue()
	{
	}

	template< typename T >
	void thread_safe_queue< T >::push( const T& value )
	{
		boost::mutex::scoped_lock lock( lock_access_ );
		data_.push( value );
	}

	template< typename T >
	bool thread_safe_queue< T >::pop( T& value )
	{
		boost::mutex::scoped_lock lock( lock_access_ );
		if( data_.empty() )
			return false;
		else
		{
			value = data_.front();
			data_.pop();
			return true;
		}
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
	{
		boost::mutex::scoped_lock lock( lock_access_ );
		return data_.empty();
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
	{
		boost::mutex::scoped_lock lock( lock_access_ );
		return data_.size();
	}

}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
