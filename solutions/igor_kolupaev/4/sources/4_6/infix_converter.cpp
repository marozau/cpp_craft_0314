#include "infix_converter.h"
#include "infix_reader.h"

void expression_calc::infix_converter::convert_to_rpn( const std::string &infix, rpn_queue_t &output )
{
	output_ = &output;

	expression_calc::infix_reader reader( infix );

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
		stack_.pop();
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

void expression_calc::infix_converter::add_operator( const std::string &s )
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