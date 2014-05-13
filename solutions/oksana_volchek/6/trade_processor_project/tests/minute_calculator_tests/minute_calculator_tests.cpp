#include "test_registrator.h"

#include <string>

#include <consts.h>
#include <minute_calculator.h>
#include <thread_safe_queue.h>
#include <trade_message.h>
#include <quote_message.h>

void minute_calculator::tests_::minute_calculator_tests()
{	
	typedef boost::shared_ptr< multicast_communication::trade_message> trade_message_ptr;
	typedef queue::thread_safe_queue< trade_message_ptr > tr_queue;
	typedef boost::shared_ptr< multicast_communication::quote_message > quote_message_ptr;
	typedef queue::thread_safe_queue< quote_message_ptr > qt_queue;
	typedef boost::shared_ptr< tr_queue > trade_queue_ptr;
	typedef boost::shared_ptr< qt_queue > quote_queue_ptr;

	BOOST_CHECK_NO_THROW(

		trade_queue_ptr t(new tr_queue);
		quote_queue_ptr q (new qt_queue);

		boost::shared_ptr<minute_calculator> qm (new minute_calculator(t, q));

		BOOST_CHECK_EQUAL( qm->get_current_time(), 0 );
	)

	{

		trade_queue_ptr t(new tr_queue);
		quote_queue_ptr q (new qt_queue);
	
		std::ifstream in;
		in.open(SOURCE_DIR  "/tests/data/t_data.udp");
		if (!in.is_open()){
			std::cout << "File was not found" << std::endl;
		}
		std::string one_msg;
		while (!in.eof()){
			std::string one_block = "";
			std::getline(in, one_block);
			for (std::string::iterator iter = one_block.begin(); iter != one_block.end(); ++iter) {
				if (*iter != consts::separator::start_block && *iter != consts::separator::end_block && *iter != consts::separator::start_inner_block){
					one_msg.push_back(*iter);
				}
				else if (*iter == consts::separator::end_block || *iter == consts::separator::start_inner_block) {
					const trade_message_ptr p(new multicast_communication::trade_message(one_msg));
					t->push(p);
					one_msg = "";
				}
			}
		}
		in.close();

		std::ifstream input;
		input.open(SOURCE_DIR  "/tests/data/q_data.udp");
		if (!input.is_open()){
			std::cout << "File was not found" << std::endl;
		}
		while (!input.eof()){
			std::string one_block = "";
			std::getline(input, one_block);
			for (std::string::iterator iter = one_block.begin(); iter != one_block.end(); ++iter) {
				if (*iter != consts::separator::start_block && *iter != consts::separator::end_block && *iter != consts::separator::start_inner_block){
					one_msg.push_back(*iter);
				}
				else if (*iter == consts::separator::end_block || *iter == consts::separator::start_inner_block) {
					const quote_message_ptr p(new multicast_communication::quote_message(one_msg));
					q->push(p);
					one_msg = "";
				}
			}
		}
		input.close();

		boost::shared_ptr<minute_calculator> qm (new minute_calculator(t, q));
		boost::this_thread::sleep(boost::posix_time::milliseconds(150));
		BOOST_CHECK_EQUAL( qm->get_current_time(), 3608965560 );


		FILE* fp;
		if( (fp = fopen(BINARY_DIR  "/datafeed/ADM.dat","rb")) != NULL ) 
		{
			boost::uint32_t time;
			double start_price, max_price, min_price, close_price, volume, bid, offer;

			fread( &time, sizeof(boost::uint32_t), 1, fp );
			fread( &start_price, sizeof(double), 1, fp );
			fread( &max_price, sizeof(double), 1, fp );
			fread( &min_price, sizeof(double), 1, fp );
			fread( &close_price, sizeof(double), 1, fp );
			fread( &volume, sizeof(double), 1, fp );
			fread( &bid, sizeof(double), 1, fp );
			fread( &offer, sizeof(double), 1, fp );
			fclose(fp);

			BOOST_CHECK_EQUAL( start_price , 15.0 );
			BOOST_CHECK_EQUAL( max_price , 97.9 );
			BOOST_CHECK_EQUAL( min_price , 10.0 );
			BOOST_CHECK_EQUAL( close_price , 35.9 );
			BOOST_CHECK_EQUAL( volume , 1000.0 );
			BOOST_CHECK_EQUAL( bid , 20.0 );
			BOOST_CHECK_EQUAL( offer , 10.0 );
		}
		qm->stop();
	}
}
