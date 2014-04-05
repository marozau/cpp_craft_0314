#pragma once

#include <stack>
#include "expression_calc.h"

namespace expression_calc
{
	class infix_converter
	{
		std::stack<std::string> stack_;
		rpn_queue_t *output_;

		void add_operator( const std::string &s );
		void add_brackets();

	public:
		void convert_to_rpn( const std::string &infix, rpn_queue_t &output );
	};
}

