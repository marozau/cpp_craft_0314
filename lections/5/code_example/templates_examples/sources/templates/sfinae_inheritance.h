#ifndef _TEMPLATES_SFINAE_H_
#define _TEMPLATES_SFINAE_H_

#include <string>

namespace templates
{
	class inheritance_from
	{
		typedef void inheritance_test_member;
	};

	template< typename T >
	class inheritance_test	
	{
		typedef char yes[1];
		typedef char no[2];

		template< typename T2 >
		static yes& check_helper( typename T2::inheritance_test_member* );

		template< typename >
		static no& check_helper( ... );

	public:
		static const bool check;

	};

	template< typename T >
	const bool inheritance_test< T >::check = ( 
		sizeof( inheritance_test< T >::check_helper< T >( NULL ) ) 
		== sizeof( inheritance_test< T >::yes ) );


	struct A1 : public inheritance_from
	{
	};

	struct B1
	{
	};

}

#endif // _TEMPLATES_SFINAE_H_
