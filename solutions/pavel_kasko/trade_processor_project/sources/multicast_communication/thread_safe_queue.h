#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE

#include <queue>
#include <boost\thread.hpp>

template<class T>
class  thread_safe_queue
{
	boost::mutex locker;
	std::queue<T> _queue;
public:
	void push(const T& element);
	T& pop();
	bool IsEmpty();
};

template<class T>
void thread_safe_queue<T>::push(const T& element)
{
	boost::mutex::scoped_lock(locker);

	_queue.push(element);
}

template<class T>
T& thread_safe_queue<T>::pop()
{
	boost::mutex::scoped_lock(locker);
	if (!IsEmpty)
		return _queue.front();
}

template<class T>
bool thread_safe_queue<T>::IsEmpty()
{
	return _queue.empty();
}

#endif //THREAD_SAFE_QUEUE