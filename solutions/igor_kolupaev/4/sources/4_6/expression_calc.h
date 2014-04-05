#pragma once

#include <string>
#include <queue>
#include <map>

namespace expression_calc
{
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

	typedef std::queue<std::string> rpn_queue_t;
	typedef std::map<std::string, std::string> variables_map_t;

	const char* operators();

	bool is_numeric( const std::string& s );
	bool is_variable( const std::string& s );
	bool is_operand( const std::string& s );
	bool is_operator( const std::string& s );
	unsigned int prio( const std::string& op );
	bool is_left_associative( const std::string& op );
}