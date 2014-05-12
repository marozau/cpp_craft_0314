#include "minute_calculator.h"
#include <stdexcept>
#include <windows.h>
#include <stdio.h>

minute_calculator::minute_calculator::minute_calculator(tr_queue & main_trade_queue, qt_queue & main_quote_queue):
	t_pointer_ (&main_trade_queue), q_pointer_ (&main_quote_queue), is_active_ (true),
	datafeed_ (std::map<std::string, minute_datafeed>()), current_time_ (0)
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
	while (is_active_) {
		if (!t_pointer_->empty()) {
			process_trade_msg();
		}
		if (!q_pointer_->empty()) {
			process_quote_msg();
		}
	}
}

void minute_calculator::minute_calculator::stop(){
	if (!is_active_){
		return;
	}
	is_active_ = false;
	print_datafeed();
	clear_datafeed();
}

void minute_calculator::minute_calculator::process_trade_msg(){
	trade_message_ptr t_msg;
	mtx_.lock();
	t_pointer_->pop(t_msg);
	mtx_.unlock();
	
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
}

void minute_calculator::minute_calculator::process_quote_msg(){
	quote_message_ptr q_msg;
	mtx_.lock();
	q_pointer_->pop(q_msg);
	mtx_.unlock();

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
}

void minute_calculator::minute_calculator::init_stockname(std::string s){
	datafeed_.insert(std::make_pair(s, minute_datafeed()));
	datafeed_[s].open_price = 0;
	datafeed_[s].high_price = 0;
	datafeed_[s].low_price = 0;
	datafeed_[s].close_price = 0;
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