#include "minute_calculator.h"
#include <stdexcept>
#include <windows.h>
#include <stdio.h>

minute_calculator::minute_calculator::minute_calculator(trade_queue_ptr & main_trade_queue, quote_queue_ptr & main_quote_queue):
	t_pointer_ (main_trade_queue), is_active_ (true), current_time_ (0), q_pointer_ (main_quote_queue),
	datafeed_ (std::map<std::string, minute_datafeed>())

{
	if(!CreateDirectory(BINARY_DIR "/datafeed/", NULL)) {
        CreateDirectory(BINARY_DIR "/datafeed/", NULL);
	}
	start();
}

minute_calculator::minute_calculator::~minute_calculator(){
	stop();
}

void minute_calculator::minute_calculator::start(){
	
	threads_.create_thread(boost::bind(&minute_calculator::process_trade_msg, this));
	threads_.create_thread(boost::bind(&minute_calculator::process_quote_msg, this));
}

void minute_calculator::minute_calculator::stop(){
	if (!is_active_){
		return;
	}
	is_active_ = false;
	print_datafeed();
	clear_datafeed();
	threads_.join_all();
}

void minute_calculator::minute_calculator::process_trade_msg(){
	while (is_active_) {
		if (!t_pointer_->empty()) {
			boost::shared_ptr< multicast_communication::trade_message> t_msg (new multicast_communication::trade_message());
			t_pointer_->pop(t_msg);
			t_mtx_.lock();	
			if (t_msg->time() > current_time_) {
				if (current_time_ > 0) {
					print_datafeed();
					clear_datafeed();
				}
				current_time_ = t_msg->time();
			}
			const std::string stockname = t_msg->security_symbol();
			if (datafeed_.count(stockname) == 0) {
				init_stockname(stockname);
			}
			if (datafeed_[stockname].currently_is_active == false) {
				datafeed_[stockname].currently_is_active = true;
				datafeed_[stockname].open_price = t_msg->price();
				datafeed_[stockname].high_price = t_msg->price();
				datafeed_[stockname].low_price = t_msg->price();
			}
			else if (t_msg->price() > datafeed_[stockname].high_price) {
				datafeed_[stockname].high_price = t_msg->price();
			}
			else if (t_msg->price() < datafeed_[stockname].low_price) {
				datafeed_[stockname].low_price = t_msg->price();
			}
			datafeed_[stockname].close_price = t_msg->price();
			datafeed_[stockname].volume += t_msg->volume();
			t_mtx_.unlock();
		}
	}
}

void minute_calculator::minute_calculator::process_quote_msg(){
	while (is_active_) {
		if (!q_pointer_->empty()) {
			boost::shared_ptr< multicast_communication::quote_message> q_msg (new multicast_communication::quote_message());
			q_pointer_->pop(q_msg);
			q_mtx_.lock();
			if (q_msg->time() > current_time_) {
				if (current_time_ > 0) {
					print_datafeed();
					clear_datafeed();
				}
				current_time_ = q_msg->time();
			}
			const std::string stockname = q_msg->security_symbol();
			if (datafeed_.count(stockname) == 0) {
				init_stockname(stockname);
			}
			if (datafeed_[stockname].currently_is_active == false) {
				datafeed_[stockname].currently_is_active = true;
			}
			datafeed_[stockname].bid += q_msg->bid_volume();
			datafeed_[stockname].offer += q_msg->offer_volume();
			q_mtx_.unlock();
		}
	}
}

void minute_calculator::minute_calculator::init_stockname(const std::string s){
	datafeed_.insert(std::make_pair(s, minute_datafeed()));
	datafeed_[s].open_price = 0.0;
	datafeed_[s].high_price = 0.0;
	datafeed_[s].low_price = 0.0;
	datafeed_[s].close_price = 0.0;
	datafeed_[s].volume = 0;
	datafeed_[s].bid = 0;
	datafeed_[s].offer = 0;
	datafeed_[s].currently_is_active = false;
}

void minute_calculator::minute_calculator::print_datafeed(){
	for (std::map<std::string, minute_datafeed>::iterator iter = datafeed_.begin(); iter != datafeed_.end(); ++iter) {
		if (datafeed_[iter->first].currently_is_active == true) {
			std::ofstream fileout(BINARY_DIR "/datafeed/" + iter->first + ".dat", std::ios::binary | std::fstream::app);
			minute_datafeed* m = &datafeed_[iter->first];
			fileout.write(reinterpret_cast<const char *>(&current_time_), sizeof(current_time_));
			fileout.write(reinterpret_cast<const char *>(&m->open_price), sizeof(m->open_price));
			fileout.write(reinterpret_cast<const char *>(&m->high_price), sizeof(m->high_price));
			fileout.write(reinterpret_cast<const char *>(&m->low_price), sizeof(m->low_price));
			fileout.write(reinterpret_cast<const char *>(&m->close_price), sizeof(m->close_price));
			fileout.write(reinterpret_cast<const char *>(&m->volume), sizeof(m->volume));
			fileout.write(reinterpret_cast<const char *>(&m->bid), sizeof(m->bid));
			fileout.write(reinterpret_cast<const char *>(&m->offer), sizeof(m->offer));
			fileout.close();
		}
	}
}

void minute_calculator::minute_calculator::clear_datafeed(){
	for (std::map<std::string, minute_datafeed>::iterator iter = datafeed_.begin(); iter != datafeed_.end(); ++iter) {
		init_stockname(iter->first);
	}
}

const boost::uint32_t minute_calculator::minute_calculator::get_current_time() const {
	return current_time_;
}