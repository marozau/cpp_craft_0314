#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>
#include <exception>

namespace task5_5
{
	template< typename T >
	class vector
	{
		size_t size_;
		size_t capacity_;
		T* vec;
		void change_capacity(size_t size);
	public:
		typedef T* iterator ; 
		typedef const T* const_iterator; 
		explicit vector();
		vector(const vector& copy);
		vector& operator=(const vector& copy_from);
		void push_back(const T& value);
		void insert(const size_t index, const T& value);

		T& operator[](const size_t index);
		const T& operator[](const size_t index) const;

		void resize(const size_t size);
		void reserve(const size_t size);

		size_t size() const;
		size_t capacity() const;
		bool empty() const;

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;

		~vector();
	};
	template< typename T >
	void vector<T>::change_capacity(size_t size)
	{
		const size_t tmp_size=std::min(size, size_);
		T *tmp=new T[size];
		for(size_t i=0; i<tmp_size; ++i)
			tmp[i]=vec[i];
		delete[] vec;
		vec=tmp;
		capacity_=size;
	}

	template< typename T >
	vector< T >::vector():
		size_(0),capacity_(4)
	{
		vec=new T[4];	
	}
	template< typename T >
	vector< T >::vector(const vector< T >& copy)
	{
		capacity_=copy.capacity_;
		size_=copy.size_;
		vec=new int[capacity_];
		std::copy(vec,vec+size_,copy.vec);
	}

	template< typename T >
	vector< T >& vector< T >::operator=(const vector< T >& copy_from)
	{
		if (&copy_from==this) return *this;
		delete [] vec;
		capacity_=copy_from.capacity_;
		size_=copy_from.size_;
		vec=new T[capacity_];
		for(size_t i=0; i<size_; ++i)
			vec[i]=copy_from.vec [i];
		return *this;
	}

	template< typename T >
	void vector< T >::push_back(const T& value)
	{
		if(size_==capacity_)
			change_capacity(capacity_*2);
		vec[size_++]=value; 
	}

	template< typename T >
	void vector< T >::insert(const size_t position, const T& value)
	{

		if(position>=size_)
			return ;
		if(size_==capacity_)
			change_capacity(capacity_*2);
		for(size_t i=size_; i>position; --i)
			vec[i]=vec[i-1];
		vec[position]=value;
		++size_;
	}

	template< typename T >
	T& vector< T >::operator[](const size_t index)
	{
		if(index>=size_)
			throw std::out_of_range("Bad index");
		return vec[index];
	}

	template< typename T >
	const T& vector< T >::operator[](const size_t index) const
	{
		if(index>=size_)
			throw std::out_of_range("Bad index");
		return vec[index];
	}

	template< typename T >
	void vector< T >::resize(const size_t size)
	{
		if(size_<0)
			throw std::logic_error("size_ can't be negative");
		if(size>capacity_)
			change_capacity(size);
		for(size_t i=size_; i<size; ++i)
			vec[i]=T();
		size_=size;

	}

	template< typename T >
	void vector< T >::reserve(const size_t size)
	{
		if(size>capacity_)
		{
			change_capacity(size);
		}

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
		return (size_==0);
	}

	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return (vec);
	}

	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return (vec+size_);
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return (vec);
	}

	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return (vec+size_);
	}
	
	template< typename T >
	vector< T >::~vector()
	{
		delete[] vec;
	}


}

#endif // _TASK5_5_VECTOR_H_
