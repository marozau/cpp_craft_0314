#include <algorithm>

#include "solution.h"

task4_5::solution::solution( const data_type& data ): data( data )
{
}

int task4_5::solution::get_min() const
{
	if( data.size() == 0 )
	{
		return 0;
	}

	int min = std::numeric_limits< int >().max();

	for( data_type::const_iterator it = data.cbegin(); it != data.cend(); it++ )
	{
		int item_min = *( std::min_element( it->cbegin(), it->cend() ) );
		min = std::min( min, item_min );
	}

	return min;
}

int task4_5::solution::get_max() const
{
	if( data.size() == 0 )
	{
		return 0;
	}

	int max = std::numeric_limits< int >().min();

	for( data_type::const_iterator it = data.cbegin(); it != data.cend(); it++ )
	{
		int max_item = *( std::max_element( it->cbegin(), it->cend() ) );
		max = std::max( max, max_item );
	}

	return max;
}
