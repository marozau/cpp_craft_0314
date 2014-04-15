#include "rpn_calc.h"
#include "expression_calc.h"

expression_calc::rpn_calc::rpn_calc( variables_map_t &vars ): vars_(vars)
{

}

double expression_calc::rpn_calc::pop_value()
{
	std::string value = stack_.top();
	stack_.pop();

	if( is_variable( value ) )
	{
		if( vars_.count( value ) == 0 )
		{
			throw variable_notdefined_exception( value );
		}

		return atof( vars_[ value ].c_str() );
	}

	double a = atof( value.c_str() );
	return a;
}

void expression_calc::rpn_calc::calc( rpn_queue_t &queue )
{
	while( queue.size() > 0 )
	{
		if( is_operand( queue.front() ) )
		{
			stack_.push( queue.front() );
			queue.pop();
		}
		else if( is_operator( queue.front() ) )
		{
			auto op = queue.front();
			queue.pop();

			switch( op[ 0 ] )
			{
				case '+':
				{
					double b = pop_value();
					double a = pop_value();
					double res = a + b;
					push_result( res );

					break;
				}
				case '-':
				{
					double b = pop_value();
					double a = pop_value();
					double res = a - b;
					push_result( res );

					break;
				}
				case '/':
				{
					double b = pop_value();
					double a = pop_value();

					if( b == 0 )
					{
						throw zero_div_exception();
					}

					double res = a / b;
					push_result( res );

					break;
				}
				case '*':
				{
					double b = pop_value();
					double a = pop_value();
					double res = a * b;
					push_result( res );

					break;
				}
				case '=':
				{
					std::string s = stack_.top();
					stack_.pop();

					if( vars_.count( stack_.top() ) > 0 )
					{
						throw variable_redefinition_exception( stack_.top() );
					}

					vars_[ stack_.top() ] = s;
					stack_.pop();

					break;
				}
				default:
					break;
			}
		}
	}

	if( stack_.size() > 0 )
	{
		vars_[ "result" ] = stack_.top();
		stack_.pop();
	}

}

void expression_calc::rpn_calc::push_result( double d )
{
	char strbuff[ 2048 ];
	sprintf( strbuff, "%g", d );
	stack_.push( std::string( strbuff ) );
}
