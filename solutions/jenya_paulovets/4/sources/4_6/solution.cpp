#include "solution.h"
#include <iostream>


task4_6::solution::solution( const lines& calulator_lines )
{
	size_t i = 0;
	expressions exps;

	for(lines::const_iterator it = calulator_lines.begin(); it != calulator_lines.end(); it++, i++)
		rpn(*it, i, exps);

	make_values(exps);
}

bool task4_6::solution::isLexical( const std::string &var ) const
{
  for(std::string::const_iterator it = var.begin(); it != var.end(); it++)
	 if(!isalpha(*it)) return false;
  return true;
}

bool task4_6::solution::isNumber( const std::string &var ) const
{
  for(std::string::const_iterator it = var.begin(); it != var.end(); it++)
	 if(!isdigit(*it)) return false;
  return true;
}

void task4_6::solution::rpn( const std::string &line, const size_t i, expressions &exps) const
{
	lines operations;
	std::string nameOfexp;
	std::string numberOfLine;
	std::string prevVal;
	bool st = false;

	nameOfexp.push_back(line[0]);
	numberOfLine = boost::lexical_cast<std::string>(i);

	if(exps.find(nameOfexp) != exps.end())
		throw std::logic_error(std::string("such variable").append("'").append(nameOfexp).append("'").append("already exists ").append(numberOfLine));


	for(std::string::const_iterator it = line.begin(); it != line.end(); it++)
	{
		if( *it == ' ') continue;

		std::string val;

		if( !st && *it != '=' ) continue;
		else if ( !st )
		{
			st = true;
			continue;
		}

		val.push_back(*it);
		while( it + 1 != line.end() && (isdigit(*(it+1)) || *(it+1) == '.'))
		{
			val.push_back(*(++it));
		}

		if( isNumber(val) || isLexical(val) )
		{
			if( isLexical(val) && exps.find(val) == exps.end())
				throw std::logic_error(std::string("'").append(val).append("'").append(" variable not defined at line").append(numberOfLine));
			else if( isNumber(val) && prevVal == "/")
				throw std::logic_error(std::string("zero div ").append(numberOfLine));
			exps[nameOfexp].push_back( val );
		}
		else
		{
			if( (val == "+" || val =="-" || val == "*" || val =="/") &&
					(prevVal == "+" || prevVal == "-" || prevVal == "*" || prevVal == "/"))
				throw std::logic_error(std::string("not correct expression at ").append(numberOfLine).append(" line"));

			if( !operations.empty() && (operations.back() == "*" || operations.back() == "/") && (val == "-" || val == "+"))
			{
				do
				{
					exps[nameOfexp].push_back( operations.back() );
					operations.pop_back();
				}while(!operations.empty() && operations.back() != "(");
				operations.push_back( val );
			}
			else if( val == ")" )
			{

				do
				{
					exps[nameOfexp].push_back( operations.back() );
					operations.pop_back();
				}while(operations.back() != "(");
				operations.pop_back();
			}
			else
			{
				operations.push_back( val );
			}
		}
		prevVal = val;
	}
	for(lines::reverse_iterator it = operations.rbegin(); it != operations.rend(); it++)
		exps[nameOfexp].push_back( *it );
}

std::string task4_6::solution::compute(const double var1, const  double var2, const std::string &oper) const
{
	if(oper == "*") return boost::lexical_cast< std::string >( var1 * var2 );
	else if(oper == "/") return boost::lexical_cast< std::string >( var1 / var2 );
	else if(oper == "+") return boost::lexical_cast< std::string >( var1 + var2 );
	else return boost::lexical_cast< std::string >( var1 - var2 );
}

void task4_6::solution::make_values( expressions &exps )
{
	for(expressions::iterator it = exps.begin(); it != exps.end(); it++)
	{
		while(it->second.size() > 1)
		{
			std::list< std::string >::iterator itt = it->second.begin();
			std::list< std::string >::iterator itt1 = ++(it->second.begin());
			std::list< std::string >::iterator itt2 = ++++(it->second.begin());

			while( isNumber( *itt2 ) || isLexical( *itt2 ) )
			{
				itt++;
				itt1++;
				itt2++;
			}

			double var1 = 0.0;
			double var2 = 0.0;

			if( !isLexical(*itt1) )
				var2 = boost::lexical_cast< double >( *itt1 );
			else var2 = boost::lexical_cast< double >( exps[*itt1].back() );

			if( !isLexical(*itt) )
				var1 = boost::lexical_cast< double >( *itt );
			else var1 = boost::lexical_cast< double >( exps[*itt].back() );

			*itt2 = compute(var1, var2, *itt2);

			it->second.erase(itt);
			it->second.erase(itt1);
		}
		results[it->first] = static_cast< int >(round(boost::lexical_cast< double >(it->second.back())));
	}
}

int task4_6::solution::result_for( const std::string& key )
{
	return results[ key ];
}
