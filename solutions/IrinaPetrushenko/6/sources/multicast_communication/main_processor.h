#ifndef _MULTICAST_COMMUNICATION_MAIN_PROCESSOR_H_
#define _MULTICAST_COMMUNICATION_MAIN_PROCESSOR_H_

#include "market_data_processor.h"
#include "quote_message.h"
#include "trade_message.h"
#include "thread_safe_queue.h"


#include <boost/function.hpp>

#include <string>
#include <fstream>


namespace multicast_communication{

	enum message_type { QUOTE, TRADE };

	class main_processor;
	typedef boost::shared_ptr< main_processor > main_processor_ptr;

	typedef boost::function < void ( const trade_message_ptr & ) > trade_call;
	typedef boost::function < void ( const quote_message_ptr & ) > quote_call;	
	
	class main_processor : public market_data_processor{

		private:
			boost::mutex mtx_out_;
			std::ofstream out_;
			const std::string out_name_;
	
		public:
			trade_call callback_t;
			quote_call callback_q;

			explicit main_processor( const std::string& filename );
			explicit main_processor( const quote_call callback_q_, const trade_call callback_t_);
			virtual ~main_processor();

			virtual void new_trade( const trade_message_ptr& );
			virtual void new_quote( const quote_message_ptr& );
	
	};

}

#endif // _MULTICAST_COMMUNICATION_MAIN_PROCESSOR_H_
