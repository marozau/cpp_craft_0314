#pragma once

#include <string>
#include <regex>

namespace task4_6
{
	class infix_reader
	{
		bool eof_;

		static std::regex token_;

		std::string infix_;
		std::sregex_token_iterator it_;
		std::sregex_token_iterator end_;

	public:

		infix_reader( const std::string& infix );
		void read( std::string& out_string );
		bool eof() const;
	};
}

