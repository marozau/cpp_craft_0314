#ifndef _TASK5_6_THREAD_SAFE_QUEUE_H_
#define _TASK5_6_THREAD_SAFE_QUEUE_H_


#include <queue>
#include <cstdlib>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace task5_6
{

	template< typename T >
	class thread_safe_queue
	{
	public:
		explicit thread_safe_queue();
		~thread_safe_queue();

		void push( const T& new_element );
		bool pop( T& result );

		bool empty() const;
		size_t size() const;
	private:
		std::queue<T> queue_;
		mutable boost::mutex protect_queue;
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
	void thread_safe_queue< T >::push( const T& t )
	{
		boost::mutex::scoped_lock lock (protect_queue);
		queue_.push( t );
	}

	template< typename T >
	bool thread_safe_queue< T >::pop( T& t)
	{
		boost::mutex::scoped_lock lock(protect_queue);
		if(queue_.empty())
			return false;
		t = queue_.front();
		queue_.pop();
		return true;
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
	{
		boost::mutex::scoped_lock lock(protect_queue);
		return queue_.empty();
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
	{
		boost::mutex::scoped_lock lock(protect_queue);
		return queue_.size();
	}
}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
