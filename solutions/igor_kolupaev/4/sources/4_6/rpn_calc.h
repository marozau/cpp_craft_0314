#pragma once

#include <stack>
#include "expression_calc.h"

namespace expression_calc
{
	class rpn_calc
	{
		std::stack<std::string> stack_;
		rpn_queue_t output_;
		variables_map_t &vars_;

		void push_result( double d );
		double pop_value();

	public:

		rpn_calc( variables_map_t &vars );
		void calc( rpn_queue_t &queue );
	};
}
