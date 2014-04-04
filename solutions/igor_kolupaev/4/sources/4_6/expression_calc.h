#pragma once

#include <string>
#include <queue>
#include <map>

namespace expression_calc
{
	typedef std::queue<std::string> rpn_queue_t;
	typedef std::map<std::string, std::string> variables_map_t;

	const char *operators = "=+-*/";

	bool is_numeric( const std::string& s );
	bool is_variable( const std::string& s );
	bool is_operand( const std::string& s );
	bool is_operator( const std::string& s );
	unsigned int prio( const std::string& op );
	bool is_left_associative( const std::string& op );

	class infix_converter
	{
		std::stack<std::string> stack_;
		rpn_queue_t *output_;

		void add_operator( std::string &s );
		void add_brackets();

	public:
		void convert_to_rpn( const std::string &infix, rpn_queue_t &output );
	};

	class rpn_calc
	{
		std::stack<std::string> stack_;
		rpn_queue_t output_;
		variables_map_t &vars_;

		rpn_calc( const variables_map_t &vars );

	public:

		void calc( rpn_queue_t &queue );

	};

}