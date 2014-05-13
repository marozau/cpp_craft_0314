#ifndef _TASK5_6_THREAD_SAFE_QUEUE_H_
#define _TASK5_6_THREAD_SAFE_QUEUE_H_

#include <cstdlib>
#include <boost/thread.hpp>
namespace task5_6
{
	template< typename T >
	class thread_safe_queue
	{
		size_t size_;
		mutable boost::mutex size_mtx,push_mtx,pop_mtx,front_mtx,back_mtx;
		struct queue
		{
			T data;
			queue* next;
			queue(T data):data(data),next(NULL)
			{}
		};
		queue *front,*back;
	public:
		explicit thread_safe_queue();
		~thread_safe_queue();

		void push(const T& new_queue);
		bool pop(T& result);

		bool empty() const;
		size_t size() const;
	};

	template< typename T >
	thread_safe_queue< T >::thread_safe_queue():size_(0),front(NULL),back(NULL)
	{}

	template< typename T >
	thread_safe_queue< T >::~thread_safe_queue()
	{
		while (!empty())
		{
			T tmp;
			pop(tmp);
		}
	}

	template< typename T >
	void thread_safe_queue< T >::push(const T& new_queue)
	{
		boost::mutex::scoped_lock push_lock(push_mtx);
		queue *temp=new queue(new_queue);
		{
			boost::mutex::scoped_lock lock_back(back_mtx);
			if(front==NULL)
			{
				boost::mutex::scoped_lock lock_front(front_mtx);
				front=back=temp;
			}
			else
			{
				back->next=temp;
				back=temp;
			}
		}
		boost::mutex::scoped_lock lock(size_mtx);
		++size_;
	}

	template< typename T >
	bool thread_safe_queue< T >::pop(T& result)
	{
		boost::mutex::scoped_lock push_lock(push_mtx);
		if (empty())
			return false;
		{
			boost::mutex::scoped_lock lock_front(front_mtx);
			result=front->data;
		}
		{
			boost::mutex::scoped_lock lock_back(back_mtx),lock_front(front_mtx);
			if(front==back)
			{
				delete front;
				front=back=NULL;
			}
			else 
			{
				queue *move_to=front->next;
				delete front;
				front=move_to;
			}
		}
		boost::mutex::scoped_lock lock(size_mtx);
		--size_;
		return true;
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
	{
		return (size()==0);
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
	{
		boost::mutex::scoped_lock lock(size_mtx);
		return size_;
	}

}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
