#include "function_templates.h"

#include <sstream>

template< typename T1, typename T2 >
std::string templates::function_1( const T1& t1 , T2 t2 )
{
	std::stringstream result;
	result << t1 << " " << t2;
	return result.str();
}

namespace templates
{
	namespace detail
	{
		void function_1_realization();
	}
}

void templates::detail::function_1_realization()
{
	function_1< int, double >( 15, 16.0 );
}

template<>
std::string templates::function_4< double >( double t1 )
{
	return "t1_double";
}

template<>
std::string templates::function_4( int t1 )
{
	return "t1_int";
}


