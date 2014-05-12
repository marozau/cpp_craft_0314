#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>
#include <iostream>

namespace task5_5
{
	template< typename T >
	class vector
	{
	private:
		T * vec_;
		size_t size_;
		size_t capacity_;
		const static size_t min_capacity_ = 4;
	public:
		typedef T* iterator ; 
		typedef const T* const_iterator; 
	public:
		explicit vector();
		vector( const vector& copy );
		vector& operator=( const vector& copy_from );

		void push_back( const T& value );
		void insert( const size_t index, const T& value );

		T& operator[]( const size_t index );
		const T& operator[]( const size_t index ) const;

		void resize( const size_t amount );
		void reserve( const size_t amount );

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
	vector< T >::vector():size_(0),capacity_(min_capacity_),vec_(new T[min_capacity_])
	{		
	}
	template< typename T >
	vector< T >::vector( const vector< T >& v):size_(v.size()),capacity_(v.capacity())
	{
		vec_=new T [capacity_];
		for (size_t i = 0; i < size_; ++i){
			vec_[i] = v[i];
		}
	}
	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >&  v)
	{
		if (&v == this) 
			return *this;
		delete [] vec_;
		capacity_ = v.capacity_;
		vec_ = new T[capacity_];
		size_ = v.size_;
		std::copy (v.begin(), v.end(), vec_);
		return *this;
	}

	template< typename T >
	void vector< T >::push_back( const T& el)
	{
		if (size_ < capacity_){
			vec_[size_++] = el;
			return;
		}
		reserve (capacity_*2);
		vec_[size_++] = el;
	}

	template< typename T >
	void vector< T >::insert( const size_t pos, const T&  el)
	{
		if (pos > size_)
			throw std::out_of_range( "Error in insert, pos > size" );

		if (size_ < capacity_){
			for (size_t i = size_;i>=pos+1;--i)
				vec_[i] = vec_[i-1];
			vec_ [pos] = el;
			++size_;
			return;
		}
		T * temp = new T [capacity_ * 2];
		std::copy (vec_, vec_+pos,temp);
		for (size_t i = pos+1;i < size_;++i)
			temp[i] = vec_[i-1];
		temp[pos] = el;
		delete [] vec_;
		vec_ = temp;
		capacity_*=2;
		++size_;

	}

	template< typename T >
	T& vector< T >::operator[]( const size_t  pos)
	{
		if (pos >= size_)
			throw std::out_of_range( "Error in operator[], pos >= size" );
		return vec_[pos];
	}

	template< typename T >
	const T& vector< T >::operator[]( const size_t pos) const
	{
		if (pos >= size_)
			throw std::out_of_range( "Error in operator[], pos >= size" );
		return vec_[pos];
	}

	template< typename T >
	void vector< T >::resize( const size_t new_size )
	{
		if (new_size == size_) return;
		if (new_size >=size_){
			if (new_size > capacity_)
				reserve (new_size);
			for (size_t i = size_; i< capacity_;++i)
				vec_[i] = static_cast <T> (0);
			size_ = new_size;
		}
		else{
			size_ = new_size;
			for (size_t i = size_; i< capacity_;++i)
				vec_[i] = static_cast <T> (0);			
		}
		
	}
	template< typename T >
	void vector< T >::reserve( const size_t new_capacity )
	{
		if (new_capacity <= capacity_) return;
		T * temp = new T [new_capacity];
		std::copy (vec_, vec_+size_, temp);
		delete [] vec_;
		vec_ = temp;
		capacity_ = new_capacity;
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
		return (size_ == 0ul);
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return vec_;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return vec_ + size_;
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return vec_;
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return vec_ + size_;
	}
	template< typename T >
	vector< T >:: ~vector()
	{
		delete [] vec_;
	}
}

#endif // _TASK5_5_VECTOR_H_

