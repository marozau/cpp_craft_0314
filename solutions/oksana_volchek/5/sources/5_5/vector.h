#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>
#include <stdexcept>

namespace task5_5
{
	template< typename T >
	class vector
	{
		T *vecData_;
		size_t vecSize_;
		size_t vecCapacity_;

		template< typename T >
		T* reallocate_vector(vector<T> & thisVec, const size_t capacityVec){
			T* newVecData = new T[capacityVec];
			for (size_t i = 0; i < thisVec.vecSize_; ++i){
				newVecData[i] = thisVec.vecData_[i];
			}
			return newVecData;
		}
		
	public:
		typedef T* iterator ; // you could change this
		typedef const T* const_iterator; // you could change this

	public:
		explicit vector();
		vector( const vector& copy );
		vector& operator=( const vector& copy_from );
		~vector();

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
	vector< T >::vector() : 
		vecData_ (new T[4]),
		vecSize_ ( 0ul ), 
		vecCapacity_ ( 4ul )
	{
	}

	template< typename T >
	vector< T >::vector( const vector< T >&  copy) : 
		vecData_ ( new T[copy.vecCapacity_] ),
		vecSize_ ( copy.vecSize_ ),
		vecCapacity_ ( copy.vecCapacity_ )
	{
		size_t i = 0;
		for (vector<T>::const_iterator iter = copy.begin(); iter != copy.end(); ++iter){
			vecData_[i] = *iter;
			++i;
		}
	}

	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >&  copy_from)
	{
		delete [] vecData_;
		vecData_ = new T[copy_from.vecCapacity_];
		size_t i = 0;
		for (vector<T>::const_iterator iter = copy_from.begin(); iter != copy_from.end(); ++iter) {
			vecData_[i] = copy_from[i];
			++i;
		}
		this->vecCapacity_ = copy_from.vecCapacity_;
		this->vecSize_ = copy_from.vecSize_;
		return *this;
	}

	template< typename T >
	vector< T >::~vector()
	{
		delete [] vecData_;
	}

	template< typename T >
	void vector< T >::push_back( const T& value)
	{
		if (vecSize_ == vecCapacity_){
			T* newPointer = reallocate_vector(*this, 2*vecCapacity_);
			delete [] vecData_;
			vecData_ = newPointer;
			vecCapacity_ *= 2;
		}
		vecData_[vecSize_] = value;
		++vecSize_;
	}

	template< typename T >
	void vector< T >::insert( const size_t index, const T&  value)
	{
		if (index > vecSize_){
			throw std::out_of_range("Index out of range");
		}
		if (vecSize_ == vecCapacity_){
			T* newPointer = reallocate_vector(*this, 2*vecCapacity_);
			delete [] vecData_;
			vecData_ = newPointer;
			vecCapacity_ *= 2;
		}
		size_t j = vecSize_;
		while (j > index){
			vecData_[j] = vecData_[j-1];
			--j;
		}
		vecData_[j] = value;
		++vecSize_;
	}
		
	template< typename T >
	T& vector< T >::operator[]( const size_t index)
	{
		if (index >= vecSize_){
			throw std::out_of_range("Index out of range");
		}
		return vecData_[index];
	}

	template< typename T >
	const T& vector< T >::operator[]( const size_t index) const
	{
		if (index >= vecSize_){
			throw std::out_of_range("Index out of range");
		}
		return vecData_[index];
	}

	template< typename T >
	void vector< T >::resize( const size_t amount )
	{
		if (amount < vecSize_){
			vecSize_ = amount;
			T* newPointer = reallocate_vector(*this, vecCapacity_);
			delete [] vecData_;
			vecData_ = newPointer;
		}
		else if (amount > vecSize_ && amount < vecCapacity_){
			for (size_t i = vecSize_; i < amount; ++i){
				vecData_[i] = 0;
			}
			vecSize_ = amount;
		}
		else {
			vecCapacity_ = amount;
			T* newPointer = reallocate_vector(*this, vecCapacity_);
			delete [] vecData_;
			vecData_ = newPointer;
			for (size_t i = vecSize_; i < amount; ++i){
				vecData_[i] = 0;
			}
			vecSize_ = amount;
		}
	}

	template< typename T >
	void vector< T >::reserve( const size_t  amount)
	{
		if (vecCapacity_ < amount){
			T* newPointer = reallocate_vector(*this, amount);
			delete [] vecData_;
			vecData_ = newPointer;
			vecCapacity_ = amount;
		}
	}

	template< typename T >
	size_t vector< T >::size() const
	{
		return vecSize_;
	}

	template< typename T >
	size_t vector< T >::capacity() const
	{
		return vecCapacity_;
	}

	template< typename T >
	bool vector< T >::empty() const
	{
		return false;
	}

	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return &vecData_[0];
	}

	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return &vecData_[vecSize_];
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return &vecData_[0];
	}

	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return &vecData_[vecSize_];
	}
}

#endif // _TASK5_5_VECTOR_H_

