#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>
#include <stdexcept>
namespace task5_5
{
	template< typename T >
	class vector
    {
        T * data_;
        const static size_t default_capacity_ = 4;
        const static size_t capacity_coeff_ = 2;
        size_t capacity_;
        size_t size_;
	public:
        typedef T* iterator ;
        typedef const T* const_iterator;
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
    private:
        void expand_capacity( const size_t new_capacity );
        void capacity_check() ;
	};

    template < typename T >
    vector< T >::~vector(){
        delete [] data_;
    }
    template < typename T >
    void vector< T >::expand_capacity( const size_t new_capacity )
    {
        T * new_data = new T[new_capacity];
        for(size_t i = 0; i < size_; ++i){
            new_data[i] = data_[i];
        }
        capacity_ = new_capacity;
        delete [] data_;
        data_ = new_data;
    }

    template < typename T >
    void vector< T >::capacity_check()
    {
        if(size_ == capacity_ )
            expand_capacity( capacity_ * capacity_coeff_);
    }


	template< typename T >
    vector< T >::vector():data_(new T[default_capacity_]),
        capacity_( default_capacity_ ),size_(0)
    {
	}
	template< typename T >
    vector< T >::vector( const vector< T >&  vec):data_(NULL),capacity_( default_capacity_),size_(0)
    {
        *this = vec;
	}
	template< typename T >
    vector< T >& vector< T >::operator=( const vector< T >& vec )
    {
        if( &vec == this)
            return *this;
        capacity_ = vec.capacity();
        size_ = vec.size();
        if(data_)
            delete [] data_;
        data_ = new T[ capacity_ ];
        for(size_t i = 0; i < size_; ++ i){
            data_[i] = vec[i];
        }
		return *this;
	}

	template< typename T >
    void vector< T >::push_back( const T& item)
    {
        capacity_check();
        data_[ size_ ] = item;
        ++ size_;
	}

	template< typename T >
    void vector< T >::insert( const size_t pos, const T& item )
    {
        capacity_check();
        T temp,next = item;

        for(size_t i = pos; i < size_; ++i){
            temp = data_[ i ];
            data_[ i ] =  next;
            next = temp;
        }
        data_[ size_++] = next;
	}

	template< typename T >
    T& vector< T >::operator[]( const size_t  pos)
	{
        if(pos >= size_)
            throw std::out_of_range("wrong index!");
        return (data_[ pos ]);
	}

	template< typename T >
    const T& vector< T >::operator[]( const size_t  pos) const
    {
        if( pos >= size_)
            throw std::out_of_range("wrong index!");
        return const_cast< T&>(  data_[ pos ]);
	}

	template< typename T >
    void vector< T >::resize( const size_t new_size )
    {
        if(new_size > capacity_){
            expand_capacity(new_size);
            for(size_t i = size_; i < new_size; ++i)
                data_[ i ] = T();
        }
        size_ = new_size;

	}
	template< typename T >
    void vector< T >::reserve( const size_t size )
    {
        if(capacity_ < size)
            expand_capacity( size );
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
        return size_ == 0ul;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
        return data_;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
        return data_+ size_ ;
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
        return data_ ;
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
        return data_ + size_ ;
	}
}

#endif // _TASK5_5_VECTOR_H_

