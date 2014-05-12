#ifndef _TASK5_6_THREAD_SAFE_QUEUE_H_
#define _TASK5_6_THREAD_SAFE_QUEUE_H_

#include <cstdlib>
#include <boost\thread.hpp>
#include <queue>

namespace task5_6
{
	template< typename T >
	class thread_safe_queue
	{
	
	mutable boost::recursive_mutex mtx;
	std::queue< T > storage;

	public:
		explicit thread_safe_queue();
		~thread_safe_queue();

		void push( const T& new_element );
		bool pop( T& result );

		bool empty() const;
		size_t size() const;
	};

	template< typename T >
	thread_safe_queue< T >::thread_safe_queue()
	{}

	template< typename T >
	thread_safe_queue< T >::~thread_safe_queue()
	{}

	template< typename T >
	void thread_safe_queue< T >::push( const T& new_element )
	{
		boost::recursive_mutex::scoped_lock lock( mtx );
		storage.push( new_element );
	}

	template< typename T >
	bool thread_safe_queue< T >::pop( T& result )
	{
		boost::recursive_mutex::scoped_lock lock( mtx );

		if( empty() )
			return false;
		else
		{
			result = storage.front();
			storage.pop();
			return true;
		}
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
	{
		boost::recursive_mutex::scoped_lock lock( mtx );
		return storage.empty();
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
	{
		boost::recursive_mutex::scoped_lock lock( mtx );
		return storage.size();
	}
}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
