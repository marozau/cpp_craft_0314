#include "solution.h"
#include <algorithm>
#include <boost\regex.hpp>
#include <boost\algorithm\string\replace.hpp>
#include <boost\algorithm\string\split.hpp>
#include <boost\algorithm\string\classification.hpp>
#include <boost\lexical_cast.hpp>
#include <exception>
#include <cmath>


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

		if (Results.find(variable) != Results.end())
			throw std::logic_error("Key already exists");

		std::string op[] = { "+", "-", "/", "*" , "(", ")"};
		int length = sizeof(op) / sizeof(*op);
		
		for (int i = 0; i < length; ++i)
			boost::replace_all(exp_body, op[i], (op[i] == "(" ? std::string("") : std::string(" ")) + std::string(op[i]) + (op[i] == ")" ? std::string("") : std::string(" ")));
		
		if(exp_body.find("  ") != std::string::npos)
			throw std::logic_error("Incorrect expression");
		
		boost::replace_all(exp_body, "  ", " ");
		std::vector<std::string> splitted;
		boost::split(splitted, exp_body, boost::is_any_of(" "));

		Results[variable] = Count(splitted);
	}
	else
		throw std::logic_error("incorrect expression");
}

int task4_6::solution::Count(std::vector<std::string>& expression)
{
	std::stack<std::string> nums;
	std::stack<std::string> operators;
	bool wait_for_next = false;
	int wait_for_close = 0;

	for(auto i = expression.begin(); i != expression.end(); ++i)
	{
		if (*i == "(")
		{
			wait_for_next = false;
			wait_for_close++;
			operators.push(*i);
		}
		else if (wait_for_close > 0 && *i == ")")
		{
			wait_for_close--;

			std::string symbol;
			std::vector<std::string> tmp;
			while ((symbol = operators.top()) != "(")
			{
				tmp.insert(tmp.begin(), nums.top());
				nums.pop();

				tmp.insert(tmp.begin(), symbol);
				operators.pop();

				tmp.insert(tmp.begin(), nums.top());
				nums.pop();
			}
			operators.pop();

			int res = Count(tmp);
			std::string s_res = boost::lexical_cast<std::string>(res);
			nums.push(s_res);
		}
		else if (wait_for_close == 0 && *i == ")")
			throw std::logic_error("invalim expression");
			
		else if(wait_for_next)
		{
			std::string first = nums.top();
			nums.pop();
			
			std::string second = *i;
			
			std::string op = operators.top();
			operators.pop();
			
			std::string res = CountTwo(first, second, op);
			nums.push(res);

			wait_for_next = false;
		}
		else if (*i == "*" || *i == "/")
		{
			wait_for_next = true;
			operators.push(*i);
		}
		else if (*i == "+" || *i == "-")
		{
			operators.push(*i);
		}
		else
		{
			nums.push(*i);
		}
	}

	double result = CountStack(nums, operators);
	return std::floor(result + 0.5);
}

std::string task4_6::solution::CountTwo(std::string& first, std::string& second, std::string& op)
{
	try
	{
		double first_num;
		double second_num;
		std::locale loc;
		
		if (std::isalpha(first[0], loc))
			first_num = result_for(first);
		else
			first_num = boost::lexical_cast<double>(first);
		
		if (std::isalpha(second[0], loc))
			second_num = result_for(second);
		else
			second_num = boost::lexical_cast<double>(second);
		
		double res;

		if (op == "+")
			res = first_num + second_num;
		else if (op == "-")
			res = first_num - second_num;
		else if (op == "*")
			res = first_num * second_num;
		else if (op == "/" && second_num != 0)
		{
			res = first_num / second_num;
		}
		else if(op == "/" && second_num == 0)
		{
			throw std::logic_error("Divide by zero exception");
		}
			
		return boost::lexical_cast<std::string>(res);
	}
	catch (std::logic_error)
	{
		throw;
	}
	catch (std::exception)
	{
		throw std::logic_error("Key does not exist.");
	}
}

double task4_6::solution::CountStack(std::stack<std::string> stack_num, std::stack<std::string> stack_op)
{
	if (stack_num.size() - stack_op.size() != 1)
		throw std::logic_error("Invalid input parameters");
	
	std::string seed = stack_num.top();
	stack_num.pop();

	while (stack_num.size() != 0)
	{
		seed = CountTwo(stack_num.top(), seed, stack_op.top());
		stack_num.pop();
		stack_op.pop();
	}

	return boost::lexical_cast<double>(seed);
}

int task4_6::solution::result_for( const std::string& key ) const
{
	auto pos = Results.find(key);
		
	if (pos == Results.end())
		throw std::logic_error("Key not found");
		
	return pos->second;
}
