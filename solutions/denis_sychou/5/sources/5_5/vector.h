#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>

namespace task5_5
{
	template< class T >
	class vector
	{

		friend T;

	public:
		typedef T* iterator ; 
		typedef const T* const_iterator; 

		explicit vector();
		vector( const vector& copy );
		vector& operator=( const vector& copy_from );
		~vector ();

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
		T* storage_;
	
		size_t capacity_,
			   size_;
		static const size_t start_size_ = 4,
							coeficient = 2;

	};

	template< typename T >
	vector< T >::vector() : storage_( new T [ start_size_ ] ), 
							capacity_( start_size_ ),
							size_( 0 )
	{
	}
	template< typename T >
	vector< T >::vector( const vector< T >& copy )
	{
		capacity_ = copy.capacity();
		size_ = copy.size();
		storage_ = new T [ capacity_ ];
		std::copy( copy.begin(), copy.end(), storage_ );
	}
	template< typename T >
	vector< T >::~vector()
	{
		delete [] storage_;
	}
	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >& copy_from )
	{
		if( &copy_from == this )
			return *this;

		delete [] storage_;
		size_ = copy_from.size();
		capacity_ = copy_from.capacity();
		storage_ = new T [ capacity_ ];
		for( size_t i = 0; i < size_; i++ )
			storage_[ i ] = copy_from[ i ];
		return *this;
	}

	template< typename T >
	void vector< T >::push_back( const T& value )
	{
		if( size_ != capacity_ )
		{
			storage_[ size_ ] = value;
			size_++;
		}
		else
		{
			reserve( capacity_ * coeficient );
			storage_[ size_ ] = value;
			size_++;
		}
	}

	template< typename T >
	void vector< T >::insert( const size_t index, const T& value )
	{
		if( index > size_ )
			throw std::out_of_range( "Out of range" );

		if( size_ == capacity_ )
			reserve( capacity_ * coeficient );

		++size_;

		for( size_t i = size_; i != index ; i-- )
			storage_[ i ] = storage_[ i - 1 ];

		storage_[ index ] = value;
	}

	template< typename T >
	T& vector< T >::operator[]( const size_t index )
	{
		if( size_ <= index ) 
		{
			throw( std::out_of_range( "Out of range" ) );
		}
		else		
			return storage_[ index ];
	}

	template< typename T >
	const T& vector< T >::operator[]( const size_t index ) const
	{
		if( size_ <= index ) 
		{
			throw( std::out_of_range( "Out of range" ) );
		}
		else		
			return storage_[ index ];
	}

	template< typename T >
	void vector< T >::resize( const size_t amount ) 
	{
		if( amount == size_ )
			return;

		T* temp = storage_;
		size_t temp_size = std::min( amount, size_ );
		size_ = amount;
		capacity_ = std::max( capacity_ , amount );
		storage_ = new T [ capacity_ ];

		for( size_t i = 0; i < size_; i++ )
			storage_[ i ] = T( 0 );

		for( size_t i = 0; i < temp_size; i++ )
			storage_[ i ] = temp[ i ];

		delete [] temp;			
	}
	template< typename T >
	void vector< T >::reserve( const size_t amount )
	{
		if( amount > capacity_ )
		{
			T* temp = storage_;
			capacity_ = amount;
			storage_ = new T [ capacity_ ];
			for( size_t i = 0; i < size_; i++ )
				storage_[ i ] = temp[ i ];
			delete [] temp;
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
		return size_ == 0;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return &storage_[ 0 ];
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return &storage_[ size_ ];
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return &storage_[ 0 ];
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return &storage_[ size_ ];
	}
}

#endif // _TASK5_5_VECTOR_H_

