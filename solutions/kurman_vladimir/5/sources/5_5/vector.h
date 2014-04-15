#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstddef>
#include <utility>
#include <stdexcept>

namespace task5_5
{
	template< typename T >
	class vector
	{
		static_assert(!std::is_pointer<T>::value, "Class vector doesn't support pointers as data's type");
		static const size_t default_capacity = 4;
		static const size_t expanding_koeff = 2;
		T * data_;
		size_t capacity_;
		size_t size_;

	public:
		typedef T * iterator;
		typedef const T * const_iterator;

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

	private:
		void increase_capacity( const size_t amount );
		void pre_insert_check();
	};

	template< typename T >
	task5_5::vector<T>::~vector()
	{
		delete[] data_;
	}

	template< typename T >
	void task5_5::vector<T>::pre_insert_check()
	{
		if (size_ == capacity_)
			increase_capacity(capacity_ * expanding_koeff);
	}

	template< typename T >
	void task5_5::vector<T>::increase_capacity( const size_t amount )
	{
		capacity_ = amount;
		T * tempData = new T[capacity_];
		std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), tempData);
		delete[] data_;
		data_ = tempData;
	}

	template< typename T >
	vector< T >::vector() : data_(new T[default_capacity]), capacity_(default_capacity), size_(0)
	{

	}

	template< typename T >
	vector< T >::vector( const vector< T >& copy ) : data_(nullptr), capacity_(default_capacity), size_(0)
	{
		*this = copy;
	}

	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >& copy_from )
	{
		if (this == &copy_from)
			return *this;
		if (data_)
			delete[] data_;
		capacity_ = copy_from.capacity();
		size_ = copy_from.size();
		data_ = new T[capacity_];
		std::uninitialized_copy(copy_from.begin(), copy_from.end(), data_);
		return *this;
	}

	template< typename T >
	void vector< T >::push_back( const T& value )
	{
		pre_insert_check();
		data_[size_++] = value;
	}

	template< typename T >
	void vector< T >::insert( const size_t index, const T& value )
	{
		pre_insert_check();
		const size_t rightPartSize = size_ - index;
		T * rightPart = new T[rightPartSize];
		std::uninitialized_copy(std::make_move_iterator(begin() + index), std::make_move_iterator(end()), rightPart);
		*(begin() + index) = value;
		std::move(rightPart, rightPart + rightPartSize, begin() + index + 1);
		delete[] rightPart;
		++size_;
	}

	template< typename T >
	T& vector< T >::operator[]( const size_t index )
	{
		if (index >= size_)
			throw std::out_of_range("Error in vector's subscripting operator");
		return data_[index];
	}

	template< typename T >
	const T& vector< T >::operator[]( const size_t index ) const
	{
		if (index >= size_)
			throw std::out_of_range("Error in vector's subscripting operator");
		return data_[index];
	}

	template< typename T >
	void vector< T >::resize(const size_t amount)
	{
		if (amount > capacity_)
			increase_capacity(amount);
		if (amount > size_)
			std::fill(begin() + size_, begin() + amount, T());
		size_ = amount;
	}

	template< typename T >
	void vector< T >::reserve(const size_t amount)
	{
		if (capacity_ >= amount)
			return;
		delete[] data_;
		capacity_ = amount;
		size_ = 0;
		data_ = new T[capacity_];
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
		return size_ == 0;
	}

	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return data_;
	}

	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return data_ + size_;
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return const_cast<vector< T > *>(this)->begin();
	}

	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return const_cast<vector< T > *>(this)->end();
	}
}

#endif // _TASK5_5_VECTOR_H_
