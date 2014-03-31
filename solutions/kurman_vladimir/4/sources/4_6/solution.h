#ifndef _TASK4_6_SOLUTION_H_
#define _TASK4_6_SOLUTION_H_

#include <vector>
#include <string>
#include <memory>

namespace task4_6
{
	class solution_4_6_impl;

	typedef std::vector< std::string > lines;

	class solution
	{
	public:
		explicit solution(const lines & calulatorLines);
		~solution();
		int result_for(const std::string & key) const;
	private:
		std::unique_ptr<solution_4_6_impl> solutionImpl_;
	};
}

#endif // _TASK4_5_SOLUTION_H_
