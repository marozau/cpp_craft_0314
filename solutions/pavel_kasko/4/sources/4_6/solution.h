#ifndef _TASK4_6_SOLUTION_H_
#define _TASK4_6_SOLUTION_H_

#include <vector>
#include <string>
#include <map>

namespace task4_6
{
	typedef std::vector< std::string > lines;

	class solution
	{
		typedef std::map<std::string, int> Result;

		Result Results;
		void Handle(std::string& expression);
		int Count(std::string& expression);
		double CountTwo(char first, char second, char op);

	public:
		explicit solution( const lines& calulator_lines );
		int result_for( const std::string& key ) const;
	};
}

#endif // _TASK4_5_SOLUTION_H_



