#ifndef _TASK4_6_SOLUTION_H_
#define _TASK4_6_SOLUTION_H_

#include <vector>
#include <list>
#include <string>
#include <map>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <ctype.h>
#include <math.h>

namespace task4_6
{
	typedef std::vector< std::string > lines;
	typedef std::map< std::string, std::list< std::string > > expressions;
	typedef std::map< std::string , int > values;

	class solution
	{
		values results;

		void rpn( const std::string &line, const size_t i, expressions &exps) const;
		std::string compute( const  double var1, const double var2, const std::string &oper ) const;
		void make_values( expressions &exps );
		bool isLexical( const std::string &var ) const;
		bool isNumber( const std::string &var ) const;
	public:
		explicit solution( const lines& calulator_lines );
		int result_for( const std::string& key );
	};
}

#endif // _TASK4_5_SOLUTION_H_



