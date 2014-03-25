#include "stock_data.h"
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;

binary_reader::stock_data::stock_data( std::ifstream& in )
{
	if(!in.read(stock_name_, len_)) {
		if (in.eof()) return;
		cerr<<"Input is incorrect name"<<endl;
		return;
	}
	if(!in.read(date_time_, len_)) {
		if (in.eof()) return;
		cerr<<"Input is incorrect time"<<endl;
		return;
	}

    if(!in.read(reinterpret_cast<char *>(&price_), sizeof(price_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrect price"<<endl;
		return;
	}
	
	if(!in.read(reinterpret_cast<char *>(&vwap_), sizeof(vwap_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrec vwapt"<<endl;
		return;
	}
	
	if(!in.read(reinterpret_cast<char *>(&volume_), sizeof(volume_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrect volume"<<endl;
		return;
	}
	
	if(!in.read(reinterpret_cast<char *>(&f1_), sizeof(f1_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrect f1"<<endl;
		return;
	}
	
	if(!in.read(reinterpret_cast<char *>(&t1_), sizeof(t1_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrect t1"<<endl;
		return;
	}
	
	if(!in.read(reinterpret_cast<char *>(&f2_), sizeof(f2_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrect f2"<<endl;
		return;
	}
	
	if(!in.read(reinterpret_cast<char *>(&f3_), sizeof(f3_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrect f3"<<endl;
		return;
	}
	
	if(!in.read(reinterpret_cast<char *>(&f4_), sizeof(f4_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrect f4"<<endl;
		return;
	}
}
binary_reader::stock_data::stock_data( const char* stock_name,
							const char* date_time,
							const double price,
							const double vwap,
							const boost::uint32_t volume,
							const double f1,
							const double t1,
							const double f2,
							const double f3,
							const double f4 ):
							price_(price),
							vwap_(vwap),
							volume_(volume),
							f1_(f1),
							t1_(t1),
							f2_(f2),
							f3_(f3),
							f4_(f4)
							
{
	memcpy(stock_name_, stock_name, len_);
	memcpy(date_time_, date_time, len_);
}

binary_reader::stock_data::~stock_data()
{
}

void binary_reader::stock_data::write( std::ofstream& out )
{
	if(!out.write(stock_name_, len_)) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write("\0", 1)) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(date_time_, len_)) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(reinterpret_cast<char *>(&price_), sizeof(price_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(reinterpret_cast<char *>(&vwap_), sizeof(vwap_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(reinterpret_cast<char *>(&volume_), sizeof(volume_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(reinterpret_cast<char *>(&f1_), sizeof(f1_))){
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(reinterpret_cast<char *>(&t1_), sizeof(t1_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(reinterpret_cast<char *>(&f2_), sizeof(f2_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(reinterpret_cast<char *>(&f3_), sizeof(f3_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(reinterpret_cast<char *>(&f4_), sizeof(f4_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
}
void binary_reader::stock_data::write_raw( std::ofstream& out )
{	
	// your code. Can be empty
	// this method is used for testing. It writes data to the binary file without convertion.
}
void binary_reader::stock_data::write_stock_name(std::ofstream& out){
	if(!out.write(stock_name_, len_)) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write("\0", 1)) {
		cerr<<"I can not write data"<<endl;
		return;
	}
}
void binary_reader::stock_data::write_data (std::ofstream& out) const{
	boost::uint32_t temp=0;
	int year;
	int mon;
	int day;
	sscanf(date_time_, "%4d%2d%2d", &year, &mon, &day);
	temp=(year-1)*372 + (mon-1)*31 + day;
	if (!out.write(reinterpret_cast<char *>(&temp),sizeof(temp))){
		cerr<<"I can not write data"<<endl;
		return;
	}
}

void binary_reader::stock_data::write_price (std::ofstream& out){
	if(!out.write(reinterpret_cast<char *>(&vwap_), sizeof(vwap_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
}
void binary_reader::stock_data::write_volume (std::ofstream& out){
	if(!out.write(reinterpret_cast<char *>(&volume_), sizeof(volume_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
}
void binary_reader::stock_data::write_f2 (std::ofstream& out){
	if(!out.write(reinterpret_cast<char *>(&f2_), sizeof(f2_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
}