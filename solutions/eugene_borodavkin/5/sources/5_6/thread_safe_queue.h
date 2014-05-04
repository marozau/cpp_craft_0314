#ifndef _TASK5_6_THREAD_SAFE_QUEUE_H_
#define _TASK5_6_THREAD_SAFE_QUEUE_H_

#include <cstdlib>
#include <boost/thread.hpp>
#include <queue>


namespace task5_6
{
	template< typename T >
	class thread_safe_queue
    {
        mutable boost::mutex mutex_queue_;
        std::queue < T > queue_;
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
	{
	}

	template< typename T >
	thread_safe_queue< T >::~thread_safe_queue()
	{
	}

	template< typename T >
    void thread_safe_queue< T >::push( const T&  item)
	{
        boost::mutex::scoped_lock lock(mutex_queue_);
        queue_.push(item);
	}

	template< typename T >
    bool thread_safe_queue< T >::pop( T& item)
    {
        boost::mutex::scoped_lock lock(mutex_queue_);
        if(!queue_.empty()){
            item = queue_.front();
            queue_.pop();
            return true;
        }

        return false;
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
    {
        boost::mutex::scoped_lock lock(mutex_queue_);

        return queue_.empty();
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
    {
        boost::mutex::scoped_lock lock(mutex_queue_);
        return queue_.size();
	}

}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
