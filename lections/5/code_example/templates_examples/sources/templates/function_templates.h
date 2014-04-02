#ifndef _TEMPLATES_FUNCTION_TEMPLATES_H_
#define _TEMPLATES_FUNCTION_TEMPLATES_H_

#include <string>

namespace templates
{
	template< typename T1, typename T2 >
	std::string function_1( const T1& t1 , T2 t2 );

	template< typename T1, typename T2 >
	std::string function_2( const T1& t1, const T2& t2, T2 t3 )
	{
		std::stringstream s;

		if ( t1 == t2 )
			s << t3;

		return s.str();
	}

	template< typename T1, typename T2 >
	T1 function_3( const T2& t2 )
	{
		return static_cast< T1 >( t2 ) / 10;
	}

	// specialisation

	template< typename T1 >
	std::string function_4( T1 t1 )
	{
		return "casual";
	}

	template<>
	std::string templates::function_4< double >( double t1 );

	template<>
	std::string function_4( int t1 );

	//
	//

	template< typename T1 >
	std::string function_5_helper( const T1& t1, typename T1::value_type*  )
	{
		typename T1::value_type vt;
		vt;
		if ( sizeof( vt ) == sizeof( int ) )
			return "int";
		if ( sizeof( vt ) == sizeof( double ) )
			return "double";
		if ( sizeof( vt ) == sizeof( char ) )
			return "char";
	}
	template< typename T1 >
	std::string function_5_helper( const T1& t1, ... )
	{
		return "unknown";
	}

	template< typename T1 >
	std::string function_5( const T1& t1 )
	{
		return function_5_helper< T1 >( t1, 0 );
	}
}

#endif // _TEMPLATES_FUNCTION_TEMPLATES_H_
