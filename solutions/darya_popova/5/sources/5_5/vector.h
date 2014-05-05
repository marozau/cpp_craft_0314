#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>
#include <exception>
#include <algorithm>

namespace task5_5
{
	template< typename T >
	class vector
	{
		size_t size_;
		size_t capacity_;
		T * data_;

		void reallocate(const size_t new_capacity );
		void check() ;

	public:
		typedef T* iterator ; 
		typedef const T* const_iterator; 
	public:
		explicit vector();
		~vector();
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
		
	};
	

	template< typename T >
	void vector< T >:: check() 
	{
		if (capacity_ == size_)
			reallocate( capacity_ * 2);
	}

	template< typename T >
	void vector< T >::  reallocate(const size_t new_capacity )
	{
		T * new_data = new T[new_capacity];
		std::copy(data_, (data_+size_), new_data);
		capacity_ = new_capacity;
		delete []data_;
		data_ = new_data;
	}

	template< typename T >
	vector< T >::vector() : 
		size_(0), 
		capacity_(4)
	{
		data_ = new T[4];
	}
	template< typename T >
	vector< T >::vector( const vector< T >&  v2)
	{
		data_= new T[v2.capacity_];
		std:: copy(v2.begin(), v2.end(), data_);
		size_= v2.size_;
		capacity_ = v2.capacity_;
	}
	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >& v2 )
	{
		if ( &v2 == this )
			return *this;
		delete [] data_;
		size_ = v2.size_;
		capacity_ = v2.capacity_;
		data_ = new T[v2.capacity_];
		std:: copy(v2.begin(), v2.end(), data_);
		return *this;
	}
	template< typename T >
	void vector< T >::push_back( const T& value)
	{
		check();
		data_[size_]= value;
		++size_;
	}
	template< typename T >
	void vector< T >::insert( const size_t index, const T& value )
	{
		if (index>= size_)
			return;
		check();
		++size_;
		for (size_t i = size_ -1 ; i>= index+1 ; i--)
			data_[i] = data_[i-1];
		data_[index] = value;
	}
	template< typename T >
	T& vector< T >::operator[]( const size_t  index )
	{
		if( index >= size_)
			throw std:: out_of_range("Bad index!");

		return data_[index];
	}
	template< typename T >
	const T& vector< T >::operator[]( const size_t  index) const
	{
		if( index >= size_)
			throw std:: out_of_range("Bad index!");

		return data_[index];
	}
	template< typename T >
	void vector< T >::resize( const size_t amount )
	{
		if (amount < 0)
			throw std:: logic_error ("Can't resize");
		if (amount > capacity_)
		{
			reallocate(amount);
			for (size_t i = size_; i< amount; ++i)
				data_[i] = T();
		}
		size_ = amount;
	}
	template< typename T >
	void vector< T >::reserve( const size_t  amount)
	{
		if(capacity_ < amount)
			reallocate(amount);
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
		if (size_ == 0)
			return true;
		else 
			return false;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return (data_);
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return (data_+size_);
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return (data_);
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return (data_+size_);
	}
	template< typename T >
	vector< T >::~vector()
	{
		delete [] data_;
	}

}

#endif // _TASK5_5_VECTOR_H_

