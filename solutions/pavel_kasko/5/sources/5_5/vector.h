#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>

namespace task5_5
{
	template< typename T >
	class vector
	{
		T* data;
		size_t _size;
		size_t _capacity;

	public:
		typedef T* iterator ; // you could change this
		typedef const T* const_iterator; // you could change this
	public:
		explicit vector();
		vector( const vector& copy );
		~vector();

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
		_size = 0ul;
		_capacity = 4ul;
		data = new T[_capacity];
	}

	template< typename T >
	vector< T >::vector( const vector< T >&  input_vector)
	{
		_size = input_vector._size;
		_capacity = input_vector._capacity;

		data = new T[_capacity];

		for (int i = 0; i < _size; ++i)
			data[i] = input_vector[i];
	}

	template< typename T >
	vector< T >& vector< T >::operator=(const vector< T >& input_vector)
	{
		if (this != &input_vector) //check if the same object
		{
			_size = input_vector._size;
			_capacity = input_vector._capacity;

			delete[] data;
			data = new T[_capacity];

			for (int i = 0; i < _size; ++i)
				data[i] = input_vector[i];
		}
		return *this;
	}

	template< typename T >
	void vector< T >::push_back( const T& value)
	{
		if (_size == _capacity)
		{
			T* tmp = new T[_capacity];

			for (int i = 0; i < _size; ++i)
				tmp[i] = data[i];

			_capacity *= 2;

			delete[] data;
			data = new T[_capacity];

			for (int i = 0; i < _size; ++i)
				data[i] = tmp[i];

			delete[] tmp;
		}
		
		data[_size++] = value;
	}

	template< typename T >
	void vector< T >::insert( const size_t position, const T& value )
	{
		if (position > _capacity - 1)
			throw std::out_of_range("Index out of range exception.");

		if (_size == _capacity)
		{
			T* tmp = new T[_capacity];

			for (int i = 0; i < _size; ++i)
				tmp[i] = data[i];

			_capacity *= 2;

			delete[] data;
			data = new T[_capacity];

			for (int i = 0; i < _size; ++i)
				data[i] = tmp[i];

			delete[] tmp;
		}
		else
		{
			for (int i = _size; i > position; --i)
				data[i] = data[i - 1];
		}

		_size++;
		data[position] = value;
	}

	template< typename T >
	T& vector< T >::operator[]( const size_t position )
	{
		if (position >= _size)
			throw std::out_of_range("Index out of range exception");

		return data[position];
	}

	template< typename T >
	const T& vector< T >::operator[](const size_t position) const
	{
		if (position >= _size)
			throw std::out_of_range("Index out of range exception");

		return data[position];
	}

	template< typename T >
	void vector< T >::resize( const size_t new_size )
	{
		if (new_size == _size)
			return;

		T* tmp = new T[_capacity];

		for (int i = 0; i < _size; ++i)
			tmp[i] = data[i];

		delete[] data;
		data = new T[new_size];
		
		if (new_size < _size)
		{
			for (int i = 0; i < new_size; ++i)
				data[i] = tmp[i];
		}
		else if (new_size > _size)
		{
			for (int i = 0; i < new_size; ++i)
				data[i] = i < _size ? tmp[i] : 0;

			if (new_size > _capacity)
				_capacity = new_size;
		}
		
		delete[] tmp;
		_size = new_size;
	}

	template< typename T >
	void vector< T >::reserve( const size_t new_capacity )
	{
		if (new_capacity < _capacity)
			return;

		T* tmp = new T[_capacity];

		for (int i = 0; i < _size; ++i)
			tmp[i] = data[i];

		delete[] data;
		data = new T[new_capacity];

		for (int i = 0; i < _size; ++i)
			data[i] = tmp[i];

		delete[] tmp;

		_capacity = new_capacity;
	}

	template< typename T >
	size_t vector< T >::size() const
	{
		return _size;
	}
	
	template< typename T >
	size_t vector< T >::capacity() const
	{
		return _capacity;
	}
	
	template< typename T >
	bool vector< T >::empty() const
	{
		return _size == 0;
	}
	
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return data;
	}
	
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return data + _size;
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return data;
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return data + _size;
	}

	template<typename T>
	vector<T>::~vector()
	{
		delete[] data;
	}
}

#endif // _TASK5_5_VECTOR_H_

