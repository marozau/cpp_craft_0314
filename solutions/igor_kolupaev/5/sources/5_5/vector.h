#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>

namespace task5_5
{
	static size_t default_capacity = 4;

	template< typename T >
	class vector
	{
		T* items_;
		size_t capacity_;
		size_t size_;

		template< typename T >
		void expand(size_t new_capacity)
		{
			T *new_items = new T[new_capacity];

			std::copy(items_, items_ + this->size(), new_items);

			delete[] items_;
			items_ = new_items;
			capacity_ = new_capacity;
		}

		void copy_vector(vector<T>* dest, const vector<T>* src)
		{
			delete[] this->items_;

			this->items_ = new T[src->capacity_];

			std::copy(src->items_, src->items_ + src->size_, this->items_);

			this->capacity_ = src->capacity_;
			this->size_ = src->size_;
		}

	public:
		typedef T* iterator; // you could change this
		typedef const T* const_iterator; // you could change this
	public:
		explicit vector();
		~vector();

		vector(const vector& copy);
		vector& operator=(const vector& copy_from);

		void push_back(const T& value);
		void insert(const size_t index, const T& value);

		T& operator[](const size_t index);
		const T& operator[](const size_t index) const;

		void resize(const size_t amount);
		void reserve(const size_t amount);

		size_t size() const;
		size_t capacity() const;
		bool empty() const;

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;
	};

	template< typename T >
	vector< T >::vector() :size_(0), capacity_(default_capacity)
	{
		items_ = new T[capacity()];
	}

	template< typename T >
	vector< T >::~vector()
	{
		delete[] items_;
	}

	template< typename T >
	vector< T >::vector(const vector< T >& src) : vector()
	{
		copy_vector(this, &src);
	}

	template< typename T >
	vector< T >& vector< T >::operator=(const vector< T >& src)
	{
		if (&src != this)
		{
			copy_vector(this, &src);
		}

		return *this;
	}

	template< typename T >
	void vector< T >::push_back(const T& item)
	{
		if (size() + 1 > capacity())
		{
			expand<T>(capacity() * 2);
		}

		items_[size_++] = item;
	}

	template< typename T >
	void vector< T >::insert(const size_t position, const T& item)
	{
		push_back(0);

		T* dest = items_ + position + 1;
		T* src = items_ + position;
		size_t bytes_num = sizeof(T)* size_ - position - 1;
		std::memmove(dest, src, bytes_num);

		items_[position] = item;
	}

	template< typename T >
	T& vector< T >::operator[](const size_t index)
	{
		if (static_cast<long>(index) > static_cast<long>(size()) - 1)
		{
			throw std::out_of_range("index is out of vector's boundaries");
		}

		return items_[index];
	}

	template< typename T >
	const T& vector< T >::operator[](const size_t index) const
	{
		if (index + 1 > size())
		{
			throw std::out_of_range("index is out of vector's boundaries");
		}

		return items_[index];
	}

	template< typename T >
	void vector< T >::resize(const size_t size)
	{
		if (size > capacity_)
		{
			expand<T>(size);
		}
		else if (size > size_)
		{
			T *dest = items_ + size_;
			size_t count = size - size_;

			for (size_t i = 0; i < count; i++)
			{
				*dest = T();
				dest++;
			}
		}

		size_ = size;
	}

	template< typename T >
	void vector< T >::reserve(const size_t size)
	{
		if (size < this->size_)
		{
			return;
		}

		size_t save_size = this->size_;
		resize(size);
		size_ = save_size;
	}

	template< typename T >
	size_t vector< T >::size() const
	{
		return size_;
	}
	template< typename T >
	size_t vector< T >::capacity() const
	{
		return capacity_;
	}
	template< typename T >
	bool vector< T >::empty() const
	{
		return false;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return items_;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return items_ + size();
	}

	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return this->items_;
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return items_ + size();
	}
}

#endif // _TASK5_5_VECTOR_H_

