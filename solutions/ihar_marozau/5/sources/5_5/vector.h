#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>

namespace task5_5
{
	template< typename T >
	class vector
	{
	public:
		typedef T* iterator ; // you could change this
		typedef const T* const_iterator; // you could change this
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
	};

	// TODO, please realise the rest methods according to the tests

	template< typename T >
	vector< T >::vector()
	{
	}
	template< typename T >
	vector< T >::vector( const vector< T >&  )
	{
	}
	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >&  )
	{
		return *this;
	}

	template< typename T >
	void vector< T >::push_back( const T& )
	{
	}

	template< typename T >
	void vector< T >::insert( const size_t , const T&  )
	{
	}

	template< typename T >
	T& vector< T >::operator[]( const size_t  )
	{
		return *(new T());
	}

	template< typename T >
	const T& vector< T >::operator[]( const size_t  ) const
	{
		return *(new T());
	}

	template< typename T >
	void vector< T >::resize( const size_t  )
	{
	}
	template< typename T >
	void vector< T >::reserve( const size_t  )
	{
	}

	template< typename T >
	size_t vector< T >::size() const
	{
		return 0ul;
	}
	template< typename T >
	size_t vector< T >::capacity() const
	{
		return 0ul;
	}
	template< typename T >
	bool vector< T >::empty() const
	{
		return false;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return new T;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return new T;
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return new T;
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return new T;
	}
}

#endif // _TASK5_5_VECTOR_H_

