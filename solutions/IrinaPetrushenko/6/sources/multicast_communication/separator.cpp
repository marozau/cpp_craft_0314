#include "separator.h"
#include "main_processor.h"
#include "quote_message.h"
#include "trade_message.h"


#include <string>

#include <boost\lexical_cast.hpp>

using namespace std;

multicast_communication::separator::separator (const string & s, const message_type t, const main_processor_ptr p):message_(s), type_(t),proc (p), callback_q( p->callback_q),callback_t( p->callback_t){
	block();
}

void multicast_communication::separator::block (){
	size_t it = 0;
	
	while ( it < message_.length() ){

			if( message_[it++] != SOH && !(it>1 && message_[it-2] == US) )
				return;

			const char mc = message_[it++];
			const char mt = message_[it++];

			if( type_ == QUOTE ){
					char * str = const_cast<char *>(message_.c_str());
					std::string ss; 
					if (( mc == 'E' || mc=='L') && mt=='D') {
						message_.copy(str,56,it);
						it+=56;
						ss=boost::lexical_cast<string>(str);
						ss.resize(56);
						quote_message_ptr msg( new quote_message ( ss, SHORT_Q , callback_q) );
						msg->segmentation(ss,SHORT_Q);
					} 
					else
					if ((mc=='E' || mc=='L' || mc=='B') && mt=='B') {
						message_.copy(str,100,it);
						it+=100;
						ss=boost::lexical_cast<string>(str);
						ss.resize(100);
						quote_message_ptr msg( new quote_message ( ss, LONG_Q, callback_q) );
						msg->segmentation(ss,LONG_Q);
					}
			}
			else    {
					char * str = const_cast<char *>(message_.c_str());
					std::string ss; 
					if ((mc=='E' || mc=='L') && mt=='I') {
						message_.copy(str,42,it);
						it+=42;
						ss=boost::lexical_cast<string>(str);
						ss.resize(42);
						trade_message_ptr msg( new trade_message (ss, SHORT_T, callback_t ) );
						msg->segmentation(ss,SHORT_T);
					} 
					else
					if ((mc=='E' || mc=='L' || mc=='B') && mt=='B') {
						message_.copy(str,80,it);
						it+=80;
						ss=boost::lexical_cast<string>(str);
						ss.resize(80);
						trade_message_ptr msg( new trade_message ( ss, LONG_T, callback_t ) );
						msg->segmentation(ss,LONG_T);
					}
				}
			
			char ct = message_[it++];
			while(it<=message_.length() && ct != ETX && ct != US)
					ct = message_[it++];
		}
}