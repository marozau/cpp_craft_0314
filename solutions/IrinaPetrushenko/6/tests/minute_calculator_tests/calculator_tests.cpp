#include "test_registrator.h"

#include <separator.h>
#include <main_processor.h>
#include <quote_message.h>
#include <trade_message.h>
#include <minute_calculator.h>

#include <fstream>
#include <boost\lexical_cast.hpp>

namespace minute_calculator{

	namespace tests_{

		class minute_calculator_test_helper {

			private:
				minute_calculator::minute_datafeed md_;

			public:
				explicit minute_calculator_test_helper (){}

				void check ( const minute_calculator::minute_datafeed_ptr& data){
					md_=*data;
				}

				bool is_equal (const minute_calculator::minute_datafeed_ptr& data){
					return ( md_== *data );
				}
		};

		typedef boost::shared_ptr<minute_calculator_test_helper> minute_calculator_test_helper_ptr;

	}
}

void minute_calculator::tests_::print_to( const minute_calculator::minute_datafeed_ptr& data ){
		std::ofstream out;
		std::string name = boost::lexical_cast<std::string> ("/") + boost::lexical_cast<std::string> (data->stock_name);
		out.open( boost::lexical_cast<std::string>(SOURCE_DIR)+"/tests/minute_data_answer" + name + ".dat", std::ios_base::binary );
		out.write( reinterpret_cast< char* >( &( *data ) ), sizeof( *data ) );
		out.close();
}


void minute_calculator::tests_::calculator_tests(){
	using namespace std;
	using namespace minute_calculator;
	using namespace multicast_communication;

	typedef boost::shared_ptr< calculator > calculator_ptr;

	BOOST_CHECK_NO_THROW(

		ifstream inn;
		string message;
		const calculator_ptr calc = calculator_ptr ( new minute_calculator::calculator ( &minute_calculator::tests_::print_to ) );
		const main_processor_ptr proc = main_processor_ptr (new main_processor (	boost::bind( &minute_calculator::calculator::new_quote, *calc, _1 ),
																					boost::bind( &minute_calculator::calculator::new_trade, *calc, _1 )));
		for (size_t i = 0; i<8; ++i){
			inn.open(boost::lexical_cast<string>(SOURCE_DIR)+"/tests/data/233.200.79."+boost::lexical_cast<string>(i)+".udp", ios_base::in);
			getline(inn,message);
			BOOST_CHECK_NO_THROW (separator_ptr spt = separator_ptr (new separator (message,QUOTE,proc));)
			inn.close();
		}

		for (size_t i = 128; i<140; ++i){
			inn.open(boost::lexical_cast<string>(SOURCE_DIR)+"/tests/data/233.200.79."+boost::lexical_cast<string>(i)+".udp", ios_base::in);
			getline(inn,message);
			BOOST_CHECK_NO_THROW (separator_ptr spt = separator_ptr (new separator (message,TRADE,proc));)
			inn.close();
		}

	)

	BOOST_CHECK_NO_THROW(

		std::string ss("EO A  003759032T:3_073BGSR  B00004147006 B00004148004 12");
		const quote_message_ptr qm =quote_message_ptr(new quote_message (ss,SHORT_Q));
		qm->segmentation(ss, SHORT_Q);

		ss = ("AO A  000140208P:3\\806BGS@0100D00330400DF ");
		const trade_message_ptr tm =trade_message_ptr(new trade_message (ss,SHORT_T));		
		tm->segmentation(ss, SHORT_T);

		minute_calculator::minute_datafeed_ptr md = minute_calculator::minute_datafeed_ptr(new minute_calculator::minute_datafeed("BGS")) ;
		md->open_price = md->high_price = md->low_price =  md->close_price = 330400;
		md->volume = 100;
		md->ask = 4;
		md->bid = 6;
		md->minute = 603;

		const minute_calculator_test_helper_ptr help = minute_calculator_test_helper_ptr(new minute_calculator_test_helper());
		{
			const calculator_ptr calc = calculator_ptr (new minute_calculator::calculator (boost::bind (&minute_calculator_test_helper::check, &(*help), _1)));
			calc->new_quote(qm);
			calc->new_trade(tm);
		}

		BOOST_CHECK_EQUAL(help->is_equal(md), true);
	)
	
}
