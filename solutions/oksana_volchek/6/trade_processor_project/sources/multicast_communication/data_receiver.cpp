#include "data_receiver.h"
#include "consts.h"
#include "thread_safe_queue.h"
#include "trade_message.h"
#include <fstream>


multicast_communication::data_receiver::data_receiver(size_t trade_thread_size, size_t quote_thread_size, std::vector< multicast_pair > & trade_ports, 
				std::vector< multicast_pair > & quote_ports, trade_queue_ptr & main_trade_queue, quote_queue_ptr & main_quote_queue) : 
						trade_thread_size_ (trade_thread_size), quote_thread_size_ (quote_thread_size), 
						trade_ports_ (trade_ports), quote_ports_ (quote_ports), processing_ (new market_data_writer(output_)),
						t_pointer_ (main_trade_queue), q_pointer_ (main_quote_queue)
{
	output_.open(BINARY_DIR + consts::file_path::output_path, std::fstream::app);

	for (std::vector<multicast_pair>::iterator it = trade_ports_.begin(); it != trade_ports_.end(); ++it){
		multicast_communication::data_receiver::listen(trade_service_, it->first, it->second, string_trade_queue_, 't');
	}

	for (std::vector<multicast_pair>::iterator it = quote_ports_.begin(); it != quote_ports_.end(); ++it){
		multicast_communication::data_receiver::listen(quote_service_, it->first, it->second, string_quote_queue_, 'q');
	}
	
	for (size_t i = 0; i < trade_thread_size_; ++i){
		gr_threads_.create_thread(boost::bind(&multicast_communication::data_receiver::start, this, boost::ref(trade_service_)));
	}

	for (size_t i = 0; i < quote_thread_size_; ++i){
		gr_threads_.create_thread(boost::bind(&multicast_communication::data_receiver::start, this, boost::ref(quote_service_)));	
	}

	processing_threads_.create_thread(boost::bind(&multicast_communication::data_receiver::block_split, this, boost::ref(string_trade_queue_), 't'));
	processing_threads_.create_thread(boost::bind(&multicast_communication::data_receiver::block_split, this, boost::ref(string_quote_queue_), 'q'));
}

multicast_communication::data_receiver::~data_receiver(){
	stop();
}

void multicast_communication::data_receiver::stop(){
	if (!is_active_){
		return;
	}
	is_active_ = false;
	trade_service_.stop();
	quote_service_.stop();
	processing_threads_.join_all();
	output_.close();
}

void multicast_communication::data_receiver::start(boost::asio::io_service & service){
	service.run();
}

void multicast_communication::data_receiver::listen(boost::asio::io_service & service, std::string & addr, unsigned short port, queue & res, char msg_type) {
	try {	
		boost::shared_ptr<async_udp::udp_listener> one_listener(new async_udp::udp_listener(service, addr, port, res));
		listeners_.push_back(one_listener);
	}
	catch(...) {
		std::cout << "Listener was not created" << std::endl; 
	}
}

void multicast_communication::data_receiver::block_split(queue & block_queue, char identifier) {
	while (is_active_) {
		if (!block_queue.empty()) {
			std::string one_msg;
			std::string one_block;
			mtx_.lock();
			block_queue.pop(one_block);
			mtx_.unlock();
			for (std::string::iterator iter = one_block.begin(); iter != one_block.end(); ++iter) {
				if (*iter != consts::separator::start_block && *iter != consts::separator::end_block && *iter != consts::separator::start_inner_block){
					one_msg.push_back(*iter);
				}
				else if (*iter == consts::separator::end_block || *iter == consts::separator::start_inner_block) {
					boost::mutex::scoped_lock lock(mtx_);
					if (identifier == 'q') {
						const quote_message_ptr p(new multicast_communication::quote_message(one_msg));
						q_pointer_->push(p);
						processing_->new_quote(p);
					}
					else if (identifier == 't') {
						const trade_message_ptr p(new multicast_communication::trade_message(one_msg));
						t_pointer_->push(p);
						processing_->new_trade(p);
					}
					one_msg = "";
				}
			}
		}
	}
}