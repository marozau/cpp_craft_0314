#ifndef _MULTICAST_COMMUNICATION_THREAD_SAFE_QUEUE_H_
#define _MULTICAST_COMMUNICATION_THREAD_SAFE_QUEUE_H_

#include <cstdlib>
#include <queue>
#include <boost/thread.hpp>

namespace queue
{
	template< typename T >
	class thread_safe_queue
	{
		std::queue< T > qData_;
		size_t qSize_;
		mutable boost::mutex qMutex_;

	public:
		explicit thread_safe_queue();
		~thread_safe_queue();

		void push( const T& newElem );
		bool pop( T& result );

		bool empty() const;
		size_t size() const;
	};

	template< typename T >
	thread_safe_queue< T >::thread_safe_queue() : qSize_ (0ul)
	{
	}

	template< typename T >
	thread_safe_queue< T >::~thread_safe_queue()
	{
	}

	template< typename T >
	void thread_safe_queue< T >::push( const T& newElem )
	{
		boost::unique_lock<boost::mutex> lock (qMutex_);
		qData_.push(newElem);
		++qSize_;
	}


	template< typename T >
	bool thread_safe_queue< T >::pop( T& result )
	{
		boost::unique_lock<boost::mutex> lock(qMutex_);
		if (qSize_ == 0){
			 return false;
		}
		else {
			result = qData_.front();
			qData_.pop();
			--qSize_;
			return true;
		}
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
	{
		boost::unique_lock<boost::mutex> lock (qMutex_);
		return qSize_ == 0;
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
	{
		boost::unique_lock<boost::mutex> lock (qMutex_);
		return qSize_;
	}
}

#endif // _MULTICAST_COMMUNICATION_THREAD_SAFE_QUEUE_H_
