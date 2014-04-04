#include "infix_reader.h"

#include <boost/algorithm/string.hpp>

std::regex task4_6::infix_reader::token_( "(-?(\\d|\\.)+)|\\w+|\\+|-|\\*|/|=|\\(|\\)" );

task4_6::infix_reader::infix_reader( const std::string& infix ): infix_(infix)
{
	it_ = std::sregex_token_iterator( infix_.cbegin(), infix_.cend(), token_ );
	end_ = std::sregex_token_iterator();
}


void task4_6::infix_reader::read( std::string& out_string )
{
	out_string = *it_;
	boost::trim( out_string );
	it_++;
}

bool task4_6::infix_reader::eof() const
{
	return (it_ == end_);
}



