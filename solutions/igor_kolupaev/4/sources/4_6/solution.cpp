#include <stack>
#include <list>
#include <sstream>
#include <regex>

#include "solution.h"

class not_correct_expression: public std::logic_error
{
public:
	not_correct_expression(): logic_error( "not correct expression" )
	{
	}
};

class variable_notdefined_exception: public std::logic_error
{
	std::string what_;

public:
	variable_notdefined_exception( const std::string& variable_name ): logic_error( "" )
	{
		what_ = "'" + variable_name + "' variable is not defined";
	}

	virtual const char* what() const throw( )
	{
		return what_.c_str();
	}
};

class zero_div_exception: public std::logic_error
{
public:
	zero_div_exception(): logic_error( "zero div" )
	{
	}
};

class variable_redefinition_exception: public std::logic_error
{
	std::string what_;

public:
	variable_redefinition_exception( const std::string& variable_name ): logic_error( "" )
	{
		what_ = "such variable '" + variable_name + "' already exists";
	}

	virtual const char* what() const throw( )
	{
		return what_.c_str();
	}
};

class infix_reader
{
	bool eof_;
	std::istringstream stream;

public:

	infix_reader( const std::string& infix ): stream( infix )
	{
	}

	void read( std::string& out_string )
	{
		stream >> out_string;
	}

	bool eof() const
	{
		return stream.eof();
	}
};

class RPN
{
	std::vector<std::string> operators; //choisen vector type to allow multichars operators

	bool is_numeric( const std::string& s ) const
	{
		std::regex isnum( "^-?\\d+(?:\\.\\d+)?$" );
		return std::regex_match( s, isnum );
	}

	bool is_variable( const std::string& s ) const
	{
		std::regex letter( "[A-Z]" );
		return std::regex_match( s, letter );
	}

	bool is_operand( const std::string& s ) const
	{
		return is_numeric( s ) || is_variable( s );
	}

	bool is_operator( const std::string& s ) const
	{
		return prio( s ) < operators.size();
	}

	bool is_left( const std::string& op ) const
	{
		return op != "=";
	}

	unsigned int prio( const std::string& op ) const
	{
		auto p = std::find( operators.cbegin(), operators.cend(), op ) - operators.cbegin();
		return static_cast<unsigned int>( p );
	}

	std::stack<std::string> stack_;
	std::deque<std::string> output_;
	task4_6::variables_map_t &vars_;

	void add_brackets()
	{
		while( stack_.size() > 0 && stack_.top() != "(" )
		{
			output_.push_back( stack_.top() );
			stack_.pop();
		}

		if( stack_.size() == 0 )
		{
			throw not_correct_expression();
		}

		stack_.pop(); // pop "("
	}

	void add_operator( std::string &s )
	{
		bool op_left = is_left( s );
		unsigned int op_prio = prio( s );

		while( stack_.size() > 0 &&
			   is_operator( stack_.top() ) &&
			   ( ( op_left && op_prio < prio( stack_.top() ) ) || op_prio == prio( stack_.top() ) ) )
		{
			output_.push_back( stack_.top() );
			stack_.pop();
		}

		stack_.push( s );
	}

public:

	RPN( const std::string& infix, task4_6::variables_map_t &vars ): vars_( vars )
	{
		operators.push_back( "=" );
		operators.push_back( "+" );
		operators.push_back( "-" );
		operators.push_back( "*" );
		operators.push_back( "/" );

		convert_from_infix( infix );
		calc();

		if( stack_.size() > 0 )
		{
			vars_[ "result" ] = stack_.top();
			stack_.pop();
		}
	}

	double pop_value()
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

	void calc()
	{
		while( output_.size() > 0 )
		{
			if( is_operand( output_.front() ) )
			{
				stack_.push( output_.front() );
				output_.pop_front();
			}
			else if( is_operator( output_.front() ) )
			{
				auto op = output_.front();
				output_.pop_front();

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
	}

	void push_result( double d )
	{
		char strbuff[ 2048 ];
		sprintf( strbuff, "%g", d );
		stack_.push( std::string( strbuff ) );
	}

	void convert_from_infix( const std::string& infix )
	{
		infix_reader reader( infix );

		bool orerator_in_prev_it = false;

		while( !reader.eof() )
		{
			std::string s;
			reader.read( s );

			if( is_variable( s ) )
			{
				output_.push_back( s );
			}
			else if( is_numeric( s ) )
			{
				output_.push_back( s );
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
			output_.push_back( stack_.top() );
			stack_.pop();
		}
	}
};

void task4_6::solution::calc( std::string line )
{
	RPN rpl( line, vars_ );
}

task4_6::solution::solution( const lines& calulator_lines )
{
	int line_num = 1;

	try
	{
		for each ( std::string line in calulator_lines )
		{
			calc( line );
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
