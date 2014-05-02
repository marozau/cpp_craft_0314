#include "test_registrator.h"

#include <quote_message.h>
#include <separator.h>

void multicast_communication::tests_::quote_message_tests()
{
	BOOST_CHECK_NO_THROW
	(
		const quote_message qm;

		BOOST_CHECK_EQUAL( qm.security_symbol(), "" );
		BOOST_CHECK_EQUAL( qm.bid_price(), 0.0 );
		BOOST_CHECK_EQUAL( qm.bid_volume(), 0.0 );
		BOOST_CHECK_EQUAL( qm.offer_price(), 0.0 );
		BOOST_CHECK_EQUAL( qm.offer_volume(), 0.0 );
	)
	{
		const std::string ss("EO A  003759032T:J_073ADMR  B00004147006 B00004148004 12");
		const quote_message_ptr qm =quote_message_ptr(new quote_message (ss,SHORT_Q));
		BOOST_CHECK_NO_THROW ( qm->segmentation(ss, SHORT_Q);)
		BOOST_CHECK_EQUAL( qm->security_symbol(), "ADM" );
		BOOST_CHECK_EQUAL( qm->bid_price(), 4147 );
		BOOST_CHECK_EQUAL( qm->bid_volume(), 6.0 );
		BOOST_CHECK_EQUAL( qm->offer_price(), 4148 );
		BOOST_CHECK_EQUAL( qm->offer_volume(), 4.0 );
	}
	{
		const std::string ss("EO A  004393884N:Jb295EMN             0    AAAR AD0000007929000000001D0000007941000000001     A   02");	
		const quote_message_ptr qm =quote_message_ptr(new quote_message (ss,LONG_Q));

		BOOST_CHECK_NO_THROW ( qm->segmentation(ss, LONG_Q);)	
		BOOST_CHECK_EQUAL( qm->security_symbol(), "EMN        " );
		BOOST_CHECK_EQUAL( qm->bid_price(), 792900 );
		BOOST_CHECK_EQUAL( qm->bid_volume(), 1 );
		BOOST_CHECK_EQUAL( qm->offer_price(), 794100 );
		BOOST_CHECK_EQUAL( qm->offer_volume(), 1 );
		
	}
	{
		const std::string ss("EO A  003759033T:J_073ADMR  B00004147001 B00004148004 62KB00004147005 TB00004148004 ");	
		const quote_message_ptr qm =quote_message_ptr(new quote_message (ss,SHORT_Q));

		BOOST_CHECK_NO_THROW ( qm->segmentation(ss, SHORT_Q);)	
		BOOST_CHECK_EQUAL( qm->security_symbol(), "ADM" );
		BOOST_CHECK_EQUAL( qm->bid_price(), 4147 );
		BOOST_CHECK_EQUAL( qm->bid_volume(), 1 );
		BOOST_CHECK_EQUAL( qm->offer_price(), 4148 );
		BOOST_CHECK_EQUAL( qm->offer_volume(), 4 );
		
	}
	
}
