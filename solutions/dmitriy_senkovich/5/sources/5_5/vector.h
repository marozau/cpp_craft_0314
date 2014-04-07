#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>
#include <stdexcept>

namespace task5_5
{
	template< typename T >
	class vector
	{
		T *data_;
		size_t size_;
		size_t capacity_;

	public:
		typedef T* iterator ; // you could change this
		typedef const T* const_iterator; // you could change this
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

	// TODO, please realise the rest methods according to the tests

	template< typename T >
	vector< T >::vector()
	{
		size_ = 0ul;
		data_ = new T[4];
		capacity_ = 4ul;
	}
	template< typename T >
	vector< T >::vector( const vector< T >& copy_from )
	{
		data_ = new T[copy_from.capacity_];
		capacity_ = copy_from.capacity_;
		for( size_t i = 0; i < copy_from.size_; i++ )
			data_[i] = copy_from[i];
		size_ = copy_from.size_;
	}
	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >& copy_from  )
	{
		delete []data_;
		data_ = new T[copy_from.capacity_];
		capacity_ = copy_from.capacity_;
		for( size_t i = 0; i < copy_from.size_; i++ )
			data_[i] = copy_from[i];
		size_ = copy_from.size_;
		return *this;
	}

	template< typename T >
	void vector< T >::push_back( const T& value )
	{
		if( size_ != capacity_ )
			data_[size_++] = value;
		else
		{
			T* buff_data = new T[capacity_];
			for( size_t i = 0; i < size_; i++ )
				buff_data[i] = data_[i];
			delete data_;
			data_ = new T[2*capacity_];
			for( size_t i = 0; i < size_; i++ )
				data_[i] = buff_data[i];
			data_[size_++] = value;
			capacity_ = 2*capacity_;
			delete buff_data;
		}
	}

	template< typename T >
	void vector< T >::insert( const size_t index , const T& value )
	{
		if( index > size_ )
			throw std::out_of_range( "Your index is out of range" );
		if( size_ == capacity_ )
		{
			T* buff_data = new T[capacity_];
			for( size_t i = 0; i < size_; i++ )
				buff_data[i] = data_[i];
			delete data_;
			data_ = new T[2*capacity_];
			for( size_t i = 0; i < index; i++ )
				data_[i] = buff_data[i];
			data_[index] = value;
			for( size_t i = index + 1; i < size_ + 1; i++ )
				data_[i] = buff_data[i-1];
			delete buff_data;
			size_++;
			capacity_ = 2*capacity_;
		}
		else
		{ 
			for( size_t i = ( size_ + 1 ); i != index ; i-- )
				data_[i] = data_[i-1];
			data_[index] = value;
			size_++;
		}
	}

	template< typename T >
	T& vector< T >::operator[]( const size_t index )
	{
		if( index >= size_ )
			throw std::out_of_range( "Your index is out of range" );;
		return data_[index];
	}

	template< typename T >
	const T& vector< T >::operator[]( const size_t index ) const
	{
		if( index >= size_ )
			throw std::out_of_range( "Your index is out of range" );;		
		return data_[index];
	}

	template< typename T >
	void vector< T >::resize( const size_t new_size  )
	{
		if( new_size == size_ )
			return;
		if( new_size < size_ )
		{
			T* buff_data = new T[size_];
			for( size_t i = 0; i < size_; i++ )
				buff_data[i] = data_[i];
			delete data_;
			data_ = new T[capacity_];
			for( size_t i = 0; i < new_size; i++ )
				data_[i] = buff_data[i];
			delete buff_data;
			size_ = new_size;
		}
		if( ( new_size > size_ ) && ( new_size <= capacity_ ) )
		{
			for( size_t i = size_; i < new_size; i++ )
				data_[i] = static_cast< T >( 0 );
			size_ = new_size;
			return;
		}
		if( new_size > capacity_ )
		{
			T* buff_data = new T[2*capacity_];
			for( size_t i = 0; i < size_; i++ )
				buff_data[i] = data_[i];
			delete data_;
			data_ = new T[new_size];
			for( size_t i = 0; i < size_; i++ )
				data_[i] = buff_data[i];
			for( size_t i = size_; i < new_size; i++ )
				data_[i] = static_cast< T >( 0 );
			delete buff_data;
			size_ = new_size;
			capacity_ = new_size;
		}
	}
	template< typename T >
	void vector< T >::reserve( const size_t new_capacity )
	{
		if( new_capacity <= capacity_ )
			return;
		T* buff_data = new T[capacity_];
		for( size_t i = 0; i < size_; i++ )
			buff_data[i] = data_[i];
		delete data_;
		data_ = new T[new_capacity];
		for( size_t i = 0; i < size_; i++ )
			data_[i] = buff_data[i];
		delete buff_data;
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
		return ( this->begin() == this->end() );
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return &data_[0];
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return &data_[size_];
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return &data_[0];
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return &data_[size_];
	}
	template< typename T >
	vector< T >::~vector()
	{
		delete data_;
	}
	}

#endif // _TASK5_5_VECTOR_H_

