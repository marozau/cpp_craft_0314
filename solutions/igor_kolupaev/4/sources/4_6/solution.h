#ifndef _TASK4_6_SOLUTION_H_
#define _TASK4_6_SOLUTION_H_

#include <vector>
#include <string>
#include <map>
namespace task4_6
{
	typedef std::vector< std::string > lines;
	typedef std::map<std::string, std::string> variables_map_t;

	class solution
	{
		variables_map_t vars_;

		void calc( std::string line );

	public:
		explicit solution( const lines& calulator_lines );
		int result_for( const std::string& key ) const;
	};
}

#endif // _TASK4_5_SOLUTION_H_



