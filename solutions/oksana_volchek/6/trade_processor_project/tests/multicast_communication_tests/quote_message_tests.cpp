#include "test_registrator.h"

#include <quote_message.h>

void multicast_communication::tests_::quote_message_tests()
{
	BOOST_CHECK_NO_THROW
	(
		quote_message qm;

		BOOST_CHECK_EQUAL( qm.security_symbol(), "" );
		BOOST_CHECK_EQUAL( qm.bid_price(), 0.0 );
		BOOST_CHECK_EQUAL( qm.bid_volume(), 0.0 );
		BOOST_CHECK_EQUAL( qm.offer_price(), 0.0 );
		BOOST_CHECK_EQUAL( qm.offer_volume(), 0.0 );
	)

	BOOST_CHECK_NO_THROW
	(
		const std::string input_string = "KLEO A  003759034T:J_075APAR  B00009245002 B00009248001 02";
		const quote_message_ptr qm(new multicast_communication::quote_message(input_string));

		BOOST_CHECK_EQUAL( qm->security_symbol(), "" );
		BOOST_CHECK_EQUAL( qm->bid_price(), 0.0 );
		BOOST_CHECK_EQUAL( qm->bid_volume(), 0.0 );
		BOOST_CHECK_EQUAL( qm->offer_price(), 0.0 );
		BOOST_CHECK_EQUAL( qm->offer_volume(), 0.0 );
		BOOST_CHECK_EQUAL( qm->hours(), 0 );
		BOOST_CHECK_EQUAL( qm->minutes(), 0 );
	)


	BOOST_CHECK_NO_THROW
	(
		const std::string input_string = "EDEO A  003759034T:J_075APAR  B00009245002 ";
		const quote_message_ptr qm(new multicast_communication::quote_message(input_string));

		BOOST_CHECK_EQUAL( qm->security_symbol(), "" );
		BOOST_CHECK_EQUAL( qm->bid_price(), 0.0 );
		BOOST_CHECK_EQUAL( qm->bid_volume(), 0.0 );
		BOOST_CHECK_EQUAL( qm->offer_price(), 0.0 );
		BOOST_CHECK_EQUAL( qm->offer_volume(), 0.0 );
		BOOST_CHECK_EQUAL( qm->hours(), 0 );
		BOOST_CHECK_EQUAL( qm->minutes(), 0 );
	)

	BOOST_CHECK_NO_THROW
	(
		const std::string input_string = "EDEO A  003759034T:J_075APAR  B00009245002 B00009248001 02";
		const quote_message_ptr qm(new multicast_communication::quote_message(input_string));

		BOOST_CHECK_EQUAL( qm->security_symbol(), "APA" );
		BOOST_CHECK_EQUAL( qm->bid_price(), 92.45 );
		BOOST_CHECK_EQUAL( qm->bid_volume(), 2.0 );
		BOOST_CHECK_EQUAL( qm->offer_price(), 92.48 );
		BOOST_CHECK_EQUAL( qm->offer_volume(), 1.0 );
		BOOST_CHECK_EQUAL( qm->hours(), 10 );
		BOOST_CHECK_EQUAL( qm->minutes(), 26 );
	)

	BOOST_CHECK_NO_THROW
	(
		const std::string input_string = "EBEO A  003759035N:J_077ALU             0    AAAR CD0000000423000000147D0000000424000000380     A   02";
		const quote_message_ptr qm(new multicast_communication::quote_message(input_string));

		BOOST_CHECK_EQUAL( qm->security_symbol(), "ALU" );
		BOOST_CHECK_EQUAL( qm->bid_price(), 4.23 );
		BOOST_CHECK_EQUAL( qm->bid_volume(), 147.0 );
		BOOST_CHECK_EQUAL( qm->offer_price(), 4.24 );
		BOOST_CHECK_EQUAL( qm->offer_volume(), 380.0 );
		BOOST_CHECK_EQUAL( qm->hours(), 10 );
		BOOST_CHECK_EQUAL( qm->minutes(), 26 );
	)

}
