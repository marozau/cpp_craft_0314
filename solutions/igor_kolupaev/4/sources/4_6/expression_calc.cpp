#include <regex>
#include <stack>

#include "infix_reader.h"
#include "expression_calc.h"

const char* expression_calc::operators()
{
	return "=+-*/";
}

bool expression_calc::is_numeric( const std::string& s )
{
	const std::regex isnum( "^-?\\d+(?:\\.\\d+)?$" );
	return std::regex_match( s, isnum );
}

bool expression_calc::is_variable( const std::string& s )
{
	const std::regex letter( "[A-Z]" );
	return std::regex_match( s, letter );
}

bool expression_calc::is_operand( const std::string& s ) 
{
	return is_numeric( s ) || is_variable( s );
}

bool expression_calc::is_operator( const std::string& s ) 
{
	return prio( s ) < strlen( operators() );
}

unsigned int expression_calc::prio( const std::string& op )
{
	const char *ops = expression_calc::operators();
	char ch = op[ 0 ];
	unsigned int index = 0;

	while( ops[index] != '\0' && ops[index] != ch )
	{
		index++;
	}

	return index;
}

bool expression_calc::is_left_associative( const std::string& op )
{
	return op != "=";
}