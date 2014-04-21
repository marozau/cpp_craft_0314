#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost/thread.hpp>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;

	class solution
	{
        int min_;
        int max_;
        const data_type *data_;
        mutable boost::mutex max_mutex_;
        mutable boost::mutex min_mutex_;
	public:
        explicit solution( const data_type &data );
        int get_min() const;
        int get_max() const;
    private:
        void find_extremums_(const size_t index);
        void set_min_(const int min);
        void set_max_(const int max);
	};
}

#endif // _TASK4_5_SOLUTION_H_

