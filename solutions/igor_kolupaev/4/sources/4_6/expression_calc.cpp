#include <regex>
#include <stack>

#include "infix_reader.h"
#include "expression_calc.h"

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
	return prio( s ) < strlen( operators );
}

unsigned int expression_calc::prio( const std::string& op )
{
	std::string ops( expression_calc::operators );
	
	auto p = std::find( ops.cbegin(), ops.cend(), op ) - ops.cbegin();
	return static_cast<unsigned int>( p );
}

bool expression_calc::is_left_associative( const std::string& op )
{
	return op != "=";
}

void expression_calc::infix_converter::convert_to_rpn( const std::string &infix, rpn_queue_t &output )
{
	output_ = &output;

	task4_6::infix_reader reader( infix );

	bool orerator_in_prev_it = false;

	while( !reader.eof() )
	{
		std::string s;
		reader.read( s );

		if( is_variable( s ) )
		{
			output.push( s );
		}
		else if( is_numeric( s ) )
		{
			output.push( s );
		}
		else if( s == "(" )
		{
			stack_.push( s );
		}
		else if( s == ")" )
		{
			add_brackets();
		}
		else if( is_operator( s ) )
		{
			if( orerator_in_prev_it )
			{
				throw not_correct_expression();
			}

			add_operator( s );
		}

		orerator_in_prev_it = is_operator( s );
	}

	while( stack_.size() > 0 )
	{
		output.push( stack_.top() );
		stack.pop();
	}
}

void expression_calc::infix_converter::add_brackets()
{
	while( stack_.size() > 0 && stack_.top() != "(" )
	{
		output_->push( stack_.top() );
		stack_.pop();
	}

	if( stack_.size() == 0 )
	{
		throw not_correct_expression();
	}

	stack_.pop(); // pop "("
}

void expression_calc::infix_converter::add_operator( std::string &s )
{
	bool op_left = is_left_associative( s );
	unsigned int op_prio = prio( s );

	while( stack_.size() > 0 &&
		   is_operator( stack_.top() ) &&
		   ( ( op_left && op_prio < prio( stack_.top() ) ) || op_prio == prio( stack_.top() ) ) )
	{
		output_->push( stack_.top() );
		stack_.pop();
	}

	stack_.push( s );
}