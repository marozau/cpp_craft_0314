#include "solution.h"
#include <algorithm>
#include <stack>
#include <boost\regex.hpp>


task4_6::solution::solution( const lines& calulator_lines )
{
	if(calulator_lines.size() == 0)
		return;

	for (int i = 0; i < calulator_lines.size(); ++i)
	{
		std::string line = calulator_lines[i];
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		Handle(line);
	}
}

void task4_6::solution::Handle(std::string& expression)
{
	std::string pattern = "(\\w)=([\\w\\d+-/\\*\\(\\)]+)";
	boost::regex regEx(pattern);
	boost::smatch results;

	if(boost::regex_match(expression, results, regEx))
	{
		std::string variable = results[1];
		std::string exp_body = results[2];

		Results[variable] = Count(exp_body);
	}
	else
		throw std::logic_error("incorrect expression");
}

int task4_6::solution::Count(std::string& expression)
{
	std::stack<char> nums;
	std::stack<char> operators;
	bool wait_for_next = false;

	for(auto i = expression.begin(); i != expression.end(); ++i)
	{
		if(wait_for_next)
		{
			char first = nums.top();
			nums.pop();
			char second = *i;

			wait_for_next = false;
		}
	}
}

double task4_6::solution::CountTwo(char first, char second, char op)
{

}


int task4_6::solution::result_for( const std::string& key ) const
{
	return 0;
}
