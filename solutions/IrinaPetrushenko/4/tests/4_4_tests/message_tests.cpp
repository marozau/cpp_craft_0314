#include "test_registrator.h"

#include <message.h>

namespace task4_4
{
	namespace tests_
	{
		namespace detail
		{
			class message_test_helper : public task4_4::message
			{
			public:
				static message_ptr create_message()
				{
					return message_ptr( new message_test_helper() );
				}
				const char type() const
				{
					return 'T';
				}
				const std::string str() const
				{
					return "test";
				}
			};
		}
	}
}

void task4_4::tests_::message_constructor_tests()
{
	BOOST_CHECK_NO_THROW( detail::message_test_helper::create_message() );
	message_ptr ptr = detail::message_test_helper::create_message();

	BOOST_CHECK_EQUAL( ptr->type(), 'T' );
	BOOST_CHECK_EQUAL( ptr->str(), "test" );
}

