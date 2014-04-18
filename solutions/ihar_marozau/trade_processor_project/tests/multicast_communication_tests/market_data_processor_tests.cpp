#include "test_registrator.h"

#include <market_data_processor.h>

namespace multicast_communication
{
	namespace tests_
	{
		class market_data_processor_test_helper : market_data_processor
		{
		public:
			explicit market_data_processor_test_helper(){}
			virtual ~market_data_processor_test_helper(){}
		private:
			virtual void new_trade( const trade_message_ptr& );
			virtual void new_quote( const quote_message_ptr& );
		};
	}
}

void multicast_communication::tests_::market_data_processor_test_helper::new_trade( const trade_message_ptr& )
{
}
void multicast_communication::tests_::market_data_processor_test_helper::new_quote( const quote_message_ptr& )
{
}

void multicast_communication::tests_::market_data_processor_tests()
{
	BOOST_CHECK_NO_THROW
	( 
		market_data_processor_test_helper mdpth;
	)
}
