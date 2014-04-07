#include "solution.h"

#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <algorithm>

#define STRINGIFY(X) #X
#define TOSTRING(X) STRINGIFY(X)

namespace task4_6
{
	enum class EToken : char
	{
		nothing = '?', name = '!', number = '@', end = '#', plus = '+', minus = '-',
		mult = '*', div = '/', assign = '=', lp = '(', rp = ')'
	};

	const double eps = 1e-8;

	bool equalDouble(const double d1, const double d2)
	{
		return std::abs(d1 - d2) < eps;
	}

	class solution_4_6_impl
	{
	public:
		void processCalculation(const lines::value_type & expression)
		{
			inputStream_.clear();
			inputStream_ << expression;
			expr();
		}

		void verifyValid() const
		{
			if (bracketCounter_ != 0)
				throw std::logic_error(std::string("not correct expression at line ") + TOSTRING(__LINE__));
		}

		double getValue(const std::string & key) const
		{
			return variables_.at(key);
		}

		double term()
		{
			double left = prim();
			while (true)
			{
				switch (curToken_)
				{
				case EToken::mult:
					left *= prim();
					break;
				case EToken::div:
				{
					const double d = prim();
					if (equalDouble(d, 0.0))
						throw std::logic_error(std::string("zero div at line ") + TOSTRING(__LINE__));
					left /= d;
				}
					break;
				default:
					return left;
				}
			}
		}

		double prim()
		{
			get_token();
			switch (curToken_)
			{
			case EToken::number:
			{
				const double v = curNumberValue_;
				get_token();
				return v;
			}
			case EToken::name:
			{
				const std::string tempStringValue = curStringValue_;
				const bool isNewVariable = variables_.find(curStringValue_) == variables_.cend();
				if (get_token() == EToken::assign)
				{
					if (isNewVariable)
					{
						variables_[tempStringValue] = expr();
						return variables_[tempStringValue];
					}
					throw std::logic_error("such variable \'" + tempStringValue + '\'' + " already exists at line " + TOSTRING(__LINE__));
				}
				if (!isNewVariable)
					return variables_[tempStringValue];
				throw std::logic_error('\'' + tempStringValue + '\'' + " variable not defined at line " + TOSTRING(__LINE__));
			}
			case EToken::minus:
				return -prim();
			case EToken::lp:
			{
				const double e = expr();
				if (curToken_ != EToken::rp)
					throw std::logic_error(std::string("not correct expression at line ") + TOSTRING(__LINE__));
				get_token();
				return e;
			}
			default:
				throw std::logic_error(std::string("not correct expression at line ") + TOSTRING(__LINE__));
			}
		}
		double expr()
		{
			double left = term();
			while (true)
			{
				switch (curToken_)
				{
				case EToken::plus:
					left += term();
					break;
				case EToken::minus:
					left -= term();
					break;
				default:
					return left;
				}
			}
		}
		EToken get_token()
		{
			char ch;
			do
			{
				if (!inputStream_.get(ch))
					return curToken_ = EToken::end;
			}
			while (ch != '\n' && isspace(ch));
			switch (ch)
			{
			case 0:
				return curToken_ = EToken::end;
			case '(':
				++bracketCounter_;
				return curToken_ = static_cast<EToken>(ch);
			case ')':
				--bracketCounter_;
				if (bracketCounter_ < 0)
					throw std::logic_error(std::string("not correct expression at line ") + TOSTRING(__LINE__));
				return curToken_ = static_cast<EToken>(ch);
			case '*': case '/': case '+': case '-': case '=':
				return curToken_ = static_cast<EToken>(ch);
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
				inputStream_.putback(ch);
				inputStream_ >> curNumberValue_;
				return curToken_ = EToken::number;
			default:
				if (isalpha(ch))
				{
					curStringValue_ = ch;
					while (inputStream_.get(ch) && isalpha(ch))
						curStringValue_.push_back(ch);
					inputStream_.putback(ch);
					return curToken_ = EToken::name;
				};
				throw std::logic_error(std::string("not correct expression at line ") + TOSTRING(__LINE__));
			};
		}

	private:
		std::map<std::string, double> variables_;
		std::stringstream inputStream_;
		double curNumberValue_;
		std::string curStringValue_;
		int bracketCounter_ = 0;
		EToken curToken_ = EToken::nothing;
	};
}

task4_6::solution::solution(const lines& calulator_lines) : solutionImpl_(new task4_6::solution_4_6_impl)
{
	for (size_t i = 0; i < calulator_lines.size(); ++i)
	{
		solutionImpl_->processCalculation(calulator_lines[i]);
		solutionImpl_->verifyValid();
	}
}

int task4_6::solution::result_for(const std::string & key) const
{
	const double value = solutionImpl_->getValue(key);
	const bool sign = value >= 0;
	const int ans = static_cast<int>(std::floor(std::abs(value) + 0.5));
	return sign ? ans : -ans;
}

task4_6::solution::~solution()
{

}
