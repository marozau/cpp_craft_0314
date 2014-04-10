#ifndef _TASK4_6_SOLUTION_H_
#define _TASK4_6_SOLUTION_H_

#include <vector>
#include <string>

namespace task4_6
{
	typedef std::vector< std::string > lines;

	class solution
	{
	public:
		explicit solution( const lines& calulator_lines );
		int result_for( const std::string& key ) const;
	};
}

#endif // _TASK4_5_SOLUTION_H_



