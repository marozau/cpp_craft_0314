#include "solution.h"
#include <limits>
#include <boost/thread/thread.hpp>
task4_5::solution::solution( const data_type& data ):data_(data)
{
    if(data_.size() == 0){
        min_ = 0;
        max_ = 0;
        return;
    }
    max_ = std::numeric_limits< int >().min() ;
    min_ = std::numeric_limits< int >().max() ;
    boost::thread_group tg;
    for(size_t i = 0; i < data_.size(); ++i){
        tg.create_thread(  boost::bind( &task4_5::solution::find_extremums, this, i ) ) ;
    }
    tg.join_all();
}

void task4_5::solution::find_extremums(const int index)
{
    int max = std::numeric_limits<int>().min();
    int min = std::numeric_limits<int>().max();
    for( size_t i = 0; i < data_[index].size(); ++i ){
        max = std::max( max, data_[ index ][ i ] );
        min = std::min( min, data_[ index ][ i ] );
    }
    set_max( max );
    set_min( min );
}

void task4_5::solution::set_max( const int max )
{
    boost::mutex::scoped_lock lock( max_mutex_ );
    max_ = std::max( max_, max );
}

void task4_5::solution::set_min( const int min )
{
    boost::mutex::scoped_lock lock( min_mutex_ );
    min_ = std::min( min_, min );
}

int task4_5::solution::get_min() const
{
    boost::mutex::scoped_lock lock( min_mutex_ );
    return min_;
}

int task4_5::solution::get_max() const
{
    boost::mutex::scoped_lock lock( max_mutex_ );
    return max_;
}
