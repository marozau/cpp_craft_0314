#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost/thread.hpp>

namespace task4_5
{
    typedef std::vector< int > tDataElem;
	typedef std::vector< tDataElem > data_type;

	class solution
	{
	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;

    private:
        void findMinMax(const tDataElem& _element);
        int getFirstValueFromData(const data_type& _data) const;
        int getFirstValueFromDataElem(const tDataElem& _element) const;

    private:
        int m_max;
        int m_min;
        boost::mutex m_wait_max;
        boost::mutex m_wait_min;
    };
}

#endif // _TASK4_5_SOLUTION_H_

