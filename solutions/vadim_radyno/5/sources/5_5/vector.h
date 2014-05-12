#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>


namespace task5_5
{
	template< typename T >
	class vector
	{
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
        void copy(const vector& copy_from)
        {
            reserve(copy_from.capacity());
            resize(copy_from.size());

            std::copy(copy_from.begin(), copy_from.end(), begin());
        }
        void auto_reserve_if_size_inc_longer_capacity()
        {
            if (m_size + 1 > m_capacity)
            {
                reserve(m_capacity * ms_capacity_coefficient);
            }
        }

    private:
        size_t  m_capacity;
        size_t  m_size;
        T*      m_array;

        static size_t ms_start_capacity;
        static size_t ms_capacity_coefficient;
	};


	// TODO, please realise the rest methods according to the tests

    template< typename T >
    vector< T >::vector()
        : m_capacity(0)
        , m_size(0)
        , m_array(nullptr)
    {
        reserve(ms_start_capacity);
    }

	template< typename T >
	vector< T >::vector( const vector< T >& copy_from )
        : m_capacity(0)
        , m_size(0)
        , m_array(nullptr)
	{
        copy(copy_from);
	}

    template< typename T >
    task5_5::vector<T>::~vector()
    {
        if (m_array)
        {
            delete [] m_array;
            m_array = nullptr;
        }
    }

	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >& copy_from )
	{
        if (&copy_from != this)
        {
            copy(copy_from);
        }

		return *this;
	}

    template< typename T >
    void vector< T >::push_back( const T& value)
    {
        auto_reserve_if_size_inc_longer_capacity();
        m_array[m_size++] = value;
    }

    template< typename T >
    void vector< T >::insert( const size_t index, const T& value )
    {
        if (index >= m_size)
        {
            throw std::out_of_range("invalid index");
        }

        auto_reserve_if_size_inc_longer_capacity();

        ++m_size;
        for (size_t i = m_size - 1; i > index ; --i)
        {
            m_array[i] = m_array[i - 1];
        }

        m_array[index] = value;
    }

    template< typename T >
    T& vector< T >::operator[]( const size_t index )
    {
        if (index >= m_size)
        {
            throw std::out_of_range("invalid index");
        }
        return m_array[index];
    }

    template< typename T >
    const T& vector< T >::operator[]( const size_t index ) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("invalid index");
        }

        return m_array[index];
    }

    template< typename T >
    void vector< T >::resize( const size_t amount )
    {
        if (amount > m_capacity)
        {
            reserve(amount);
        }

        if (m_size < amount)
        {
            for (size_t i = m_size; i < amount; ++i)
            {
                m_array[i] = T();
            }
        }
        m_size = amount;
    }

    template< typename T >
    void vector< T >::reserve( const size_t _capacity )
    {
        if (m_capacity > _capacity)
        {
            return;
        }

        m_capacity = _capacity;

        T* change_array = new T[m_capacity];

        for (int i = 0; i < m_size; ++i)
        {
            change_array[i] = m_array[i];
        }

        if (m_array)
        {
            delete [] m_array;
            m_array = nullptr;
        }

        m_array = change_array;
    }

	template< typename T >
	size_t vector< T >::size() const
	{
		return m_size;
	}
	template< typename T >
	size_t vector< T >::capacity() const
	{
		return m_capacity;
	}
	template< typename T >
	bool vector< T >::empty() const
	{
		return m_size == 0;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
        if (0 == m_size)
        {
            return end();
        }

        return &m_array[0];
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return &m_array[m_size];
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
        if (0 == m_size)
        {
            return end();
        }

        return &m_array[0];
	}

	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return &m_array[m_size];
	}
}

#endif // _TASK5_5_VECTOR_H_

