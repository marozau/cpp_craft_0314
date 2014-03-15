#include "stock_data.h"
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;

binary_reader::stock_data::stock_data( std::ifstream& in )
{
	memset(stock_name_, 0, 8);
	if(!in.read((char *)&stock_name_, sizeof(stock_name_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}

	memset(date_time_, 0, 8);
	if(!in.read((char *)&date_time_, sizeof(date_time_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}

    if(!in.read((char *)&price_, sizeof(price_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}
	
	if(!in.read((char *)&vwap_, sizeof(vwap_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}
	
	if(!in.read((char *)&volume_, sizeof(volume_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}
	
	if(!in.read((char *)&f1_, sizeof(f1_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}
	
	if(!in.read((char *)&t1_, sizeof(t1_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}
	
	if(!in.read((char *)&f2_, sizeof(f2_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}
	
	if(!in.read((char *)&f3_, sizeof(f3_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}
	
	if(!in.read((char *)&f4_, sizeof(f4_))) {
		cerr<<"Input is incorrect"<<endl;
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
	memcpy(stock_name_, stock_name, 8 );
	memcpy(date_time_, date_time_, 8 );
}

binary_reader::stock_data::~stock_data()
{
}

void binary_reader::stock_data::write( std::ofstream& out )
{
	if(!out.write((char *)&stock_name_, sizeof(stock_name_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&date_time_, sizeof(date_time_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&price_, sizeof(price_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&vwap_, sizeof(vwap_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&volume_, sizeof(volume_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&f1_, sizeof(f1_))){
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&t1_, sizeof(t1_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&f2_, sizeof(f2_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&f3_, sizeof(f3_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&f4_, sizeof(f4_))) {
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
	if(!out.write((char *)&stock_name_, sizeof(stock_name_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
}
void binary_reader::stock_data::write_data (std::ofstream& out) const{
	boost::uint32_t temp=0;
	temp=boost::lexical_cast<unsigned int> (date_time_[3]);
	temp+=boost::lexical_cast<unsigned int> (date_time_[2])*10;
	temp+=boost::lexical_cast<unsigned int> (date_time_[1])*100;
	temp+=boost::lexical_cast<unsigned int> (date_time_[0])*1000;
	temp=(temp-1)*372;
	temp+=(boost::lexical_cast<unsigned int> (date_time_[5])+boost::lexical_cast<unsigned int> (date_time_[4])*10-1)*31;
	temp+=boost::lexical_cast<unsigned int> (date_time_[7])+boost::lexical_cast<unsigned int> (date_time_[6])*10;
	out<<temp<<endl;
}
void binary_reader::stock_data::write_price (std::ofstream& out){
	if(!out.write((char *)&vwap_, sizeof(vwap_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
}
void binary_reader::stock_data::write_volume (std::ofstream& out){
	if(!out.write((char *)&volume_, sizeof(volume_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
}
void binary_reader::stock_data::write_f2 (std::ofstream& out){
	if(!out.write((char *)&f2_, sizeof(f2_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
}