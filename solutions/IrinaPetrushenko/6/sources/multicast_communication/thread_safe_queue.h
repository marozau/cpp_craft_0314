#ifndef _TASK5_6_THREAD_SAFE_QUEUE_H_
#define _TASK5_6_THREAD_SAFE_QUEUE_H_

#include <cstdlib>
#include <queue>
#include <boost/thread.hpp>

namespace multicast_communication{

	template< typename T >
	class thread_safe_queue	{
		private:
			std::queue < T > que_;
			 mutable boost::mutex mtx_;
		public:
			explicit thread_safe_queue();
			~thread_safe_queue();

			void push( const T& new_element );
			bool pop( T& result );

			bool empty() const; 
			size_t size() const;
	}; 

	template< typename T >
	thread_safe_queue< T >::thread_safe_queue()	{
	}

	template< typename T >
	thread_safe_queue< T >::~thread_safe_queue(){
	}

	template< typename T >
	void thread_safe_queue< T >::push( const T& el ){
		boost::mutex::scoped_lock lock(mtx_);
		que_.push (el);
	}

	template< typename T >
	bool thread_safe_queue< T >::pop( T& el ){
		boost::mutex::scoped_lock lock(mtx_);
		if (que_.empty()) return false;
		el = que_.front();
		que_.pop();
		return true;
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const{
		boost::mutex::scoped_lock lock(mtx_);
		return que_.empty();
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const{
		boost::mutex::scoped_lock lock(mtx_);
		return que_.size();
	}

}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
