#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE

#include <queue>
#include <boost\thread.hpp>

template<class T>
class  thread_safe_queue
{
	mutable boost::mutex locker;
	std::queue<T> _queue;

public:
	explicit thread_safe_queue();
	~thread_safe_queue();

	void push(const T& element);
	T pop();
	bool IsEmpty();
};

template< typename T >
thread_safe_queue< T >::thread_safe_queue() { }

template< typename T >
thread_safe_queue< T >::~thread_safe_queue() { }

template<class T>
void thread_safe_queue<T>::push(const T& element)
{
	boost::mutex::scoped_lock lock(locker);

	_queue.push(element);
}

template<class T>
T thread_safe_queue<T>::pop()
{
	boost::mutex::scoped_lock lock(locker);
	if (!_queue.empty())
	{
		T elem = _queue.front();
		_queue.pop();
		return elem;
	}
}

template<class T>
bool thread_safe_queue<T>::IsEmpty()
{
	return _queue.empty();
}

#endif //THREAD_SAFE_QUEUE