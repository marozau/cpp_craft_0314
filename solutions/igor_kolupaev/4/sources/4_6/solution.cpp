#include <stack>
#include <list>
#include <sstream>
#include <regex>

#include "solution.h"
#include "infix_converter.h"
#include "rpn_calc.h"

task4_6::solution::solution( const lines& calulator_lines )
{
	int line_num = 1;

	expression_calc::rpn_calc rpn_calc( vars_ );

	try
	{
		for each ( std::string line in calulator_lines )
		{
			expression_calc::infix_converter converter;
			expression_calc::rpn_queue_t rpn_expression;

			converter.convert_to_rpn( line, rpn_expression );

			rpn_calc.calc( rpn_expression );
			line_num++;
		}
	}
	catch( std::logic_error& e )
	{
		std::ostringstream oss;
		oss << e.what() << " at line #" << line_num;
		throw std::logic_error( oss.str() );
	}
}

int task4_6::solution::result_for( const std::string& key ) const
{
	std::string s = vars_.at( key );
	int res = static_cast<int>( round( atof( s.c_str() ) ) );
	
	return res;
}
