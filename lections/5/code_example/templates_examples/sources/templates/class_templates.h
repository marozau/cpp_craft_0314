#ifndef _TEMPLATES_CLASS_TEMPLATES_H_
#define _TEMPLATES_CLASS_TEMPLATES_H_

namespace templates
{
	template< class T >
	class vector
	{
		static const size_t max_size = 1024;

		T elements_[ max_size ];
		size_t current_size_;

		vector( const vector& );
		vector& operator=( const vector& );
	public:
		explicit vector();
		~vector();

		void push_back( const T& );
		T& operator[]( const size_t index );
		T& at( const size_t index );
	};

	template< class T >
	vector< T >::vector()
		: current_size_( 0ul )
	{
	}

	template< class T >
	vector< T >::~vector()
	{
	}

	template< class T >
	void vector< T >::push_back( const T& new_element )
	{
		if ( current_size_ == max_size )
			throw std::out_of_range( "max size of elements in vector is 1024" );
		elements_[ current_size_ ] = new_element;
		++current_size_;
	}

	template< class T >
	T& vector< T >::operator[]( const size_t index )
	{
		return elements_[ index ];
	}

	template< class T >
	T& vector< T >::at( const size_t index )
	{
		if ( index >= current_size_ )
			throw std::out_of_range( "out of range, there is no element at requested index" );
		return elements_[ index ];
	}


	//
	//
	template< class T, size_t max_stack_size = 1024 >
	class  stack
	{
		struct element
		{
			T data_;
			element* prev_;
		};

		element* end_;
		size_t stack_size_;
	public:
		explicit stack();

		~stack();
		//
		void push_back( const T& new_element );
		T pop();
		//
		template< class C >
		explicit stack( const C& container );

	};
	template< class T, size_t max_stack_size >
	stack< T, max_stack_size >::stack()
		: end_( NULL )
		, stack_size_( 0ul )
	{
	}
	template< class T, size_t max_stack_size >
	stack< T, max_stack_size >::~stack()
	{
		while ( stack_size_ > 0 )
			pop();
	}


	template< class T, size_t max_stack_size >
	void stack< T, max_stack_size >::push_back( const T& new_element )
	{
		if ( stack_size_ == max_stack_size )
			throw std::out_of_range( "stack size limit" );
		
		element* new_stack_element = new element;

		new_stack_element->data_ = new_element; // copy constructor
		new_stack_element->prev_ = end_;

		end_ = new_stack_element;

		++stack_size_;
	}
	template< class T, size_t max_stack_size >
	T stack< T, max_stack_size >::pop()
	{
		if ( stack_size_ == 0 )
			throw std::out_of_range( "there is no elements in stack" );

		--stack_size_;

		element* stack_element = end_;

		end_ = stack_element->prev_;

		T result = stack_element->data_;
		delete stack_element;
		return result;
	}
	//
	//
	template< class T, size_t max_stack_size >
	template< class C >
	stack< T, max_stack_size >::stack( const C& container )
		: end_( NULL )
		, stack_size_( 0ul )
	{
		for( typename C::const_iterator i = container.begin() ; i != container.end() ; ++i )
			push_back( *i );
	}
	//
	//
	template< class T1, class T2 >
	struct pair
	{
		T1 first;
		T2 second;
	};

	template< class T1, class T2 >
	pair< T1, T2 > make_pair( const T1& t1, const T2& t2 )
	{
		pair< T1, T2 > result;
		result.first = t1;
		result.second = t2;
		return result;
	}
}

#endif // _TEMPLATES_CLASS_TEMPLATES_H_
