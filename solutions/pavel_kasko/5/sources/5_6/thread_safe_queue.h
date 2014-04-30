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
		std::queue<T> data;
		mutable boost::mutex locker;

	public:
		explicit thread_safe_queue();
		~thread_safe_queue();

		void push( const T& new_element );
		bool pop( T& result );

		bool empty() const;
		size_t size() const;
	};

	template< typename T >
	thread_safe_queue< T >::thread_safe_queue() { }

	template< typename T >
	thread_safe_queue< T >::~thread_safe_queue() { }

	template< typename T >
	void thread_safe_queue< T >::push(const T& new_element)
	{
		boost::mutex::scoped_lock lock(locker);

		data.push(new_element);
	}

	template< typename T >
	bool thread_safe_queue< T >::pop(T& result)
	{
		boost::mutex::scoped_lock lock(locker);
		
		if (data.empty())
			return false;
		
		result = data.front();
		data.pop();
		return true;
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
	{
		boost::mutex::scoped_lock lock(locker);
		return data.empty();
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
	{
		boost::mutex::scoped_lock lock(locker);
		return data.size();
	}
}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
