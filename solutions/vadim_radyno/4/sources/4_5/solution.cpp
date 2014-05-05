#include "solution.h"

task4_5::solution::solution( const data_type& data )
    : m_max(getFirstValueFromData(data))
    , m_min(m_max)
{
    boost::thread_group group_of_slave_threads;

    for ( const tDataElem& element : data)
    {
        group_of_slave_threads.create_thread( boost::bind(&task4_5::solution::findMinMax, this, boost::ref(element)) );
    }
    group_of_slave_threads.join_all();
}


int task4_5::solution::get_min() const
{
    return m_min;
}


int task4_5::solution::get_max() const
{
    return m_max;
}


int task4_5::solution::getFirstValueFromData(const data_type& _data) const
{
    for (auto data_elem : _data)
    {
        for (int current_value : data_elem)
        {
            return current_value;
        }
    }

    return 0;
}


int task4_5::solution::getFirstValueFromDataElem(const tDataElem& _element) const
{
    for (const int value : _element)
    {
        return value;
    }

    return 0;
}


void task4_5::solution::findMinMax(const tDataElem& _element)
{
    int max = getFirstValueFromDataElem(_element);
    int min = max;

    for(const int _current_value : _element) 
    {
        min = std::min( min, _current_value );
        max = std::max( max, _current_value );
    }

    {
        boost::mutex::scoped_lock lock_min(m_wait_min);
        m_min = std::min(min, m_min);
    }

    {
        boost::mutex::scoped_lock lock_max(m_wait_max);
        m_max = std::max(max, m_max);
    }
}
