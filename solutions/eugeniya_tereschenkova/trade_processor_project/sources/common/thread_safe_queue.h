#ifndef _MULTICAST_COMMUNICATION_THREAD_SAFE_QUEUE_H_
#define _MULTICAST_COMMUNICATION_THREAD_SAFE_QUEUE_H_

#include <queue>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

namespace common
{
    template< typename T >
	class thread_safe_queue
	{
	private:
		queue<T> queue_;
		bool stop_;
		boost::condition_variable condition_variable_;
		mutable boost::mutex queue_protector_; 
	public:
		explicit thread_safe_queue()
        {
            stop_ = false;
        }
        ~thread_safe_queue()
        {
            boost::mutex::scoped_lock lock(queue_protector_);
            while(!queue_.empty())
            {
                queue_.pop();
            }
            lock.unlock();
            condition_variable_.notify_all();
        }

        void push( const T& t )
        {
            boost::mutex::scoped_lock lock (queue_protector_);
            queue_.push( t );
            lock.unlock();
            condition_variable_.notify_one();
        }

        bool pop( T& t)
        {
            boost::mutex::scoped_lock lock(queue_protector_);
            if(queue_.empty())
                return false;
            t = queue_.front();
            queue_.pop();
            return true;
        }

        void wait_and_pop( T& t )
        {
            if(stop_)
                return;
            boost::mutex::scoped_lock lock(queue_protector_);
            while(queue_.empty())
            {
                condition_variable_.wait(lock);
                if(stop_)
                    return;
            }
            t = queue_.front();
            queue_.pop();
        }

        bool empty() const
        {
            boost::mutex::scoped_lock lock(queue_protector_);
            return queue_.empty();
        }

        size_t size() const
        {
            boost::mutex::scoped_lock lock(queue_protector_);
            return queue_.size();
        }

        void stop()
        {
            stop_ = true;
            condition_variable_.notify_all();
        }
	}; 
}

#endif // _MULTICAST_COMMUNICATION_THREAD_SAFE_QUEUE_H_
