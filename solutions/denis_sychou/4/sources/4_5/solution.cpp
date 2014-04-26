#include "solution.h"

task4_5::solution::solution( const data_type& data ) 
	: _min( 0 )
	, _max( 0 )
{
	if( !data.empty() )
	{
		_max = _min = ( *data.cbegin()->cbegin() );
		boost::thread_group tg;
		for( data_type::const_iterator data_it = data.cbegin(); data_it != data.cend(); data_it++ )
		{
			tg.create_thread( boost::bind( &task4_5::solution::take_extreme, this, data_it ) );
		}
		tg.join_all();

		for( data_row::const_iterator it = extreme.cbegin(); it != extreme.cend(); it++ )
		{
			_min = std::min( _min, *it );
			_max = std::max( _max, *it ); 
		}
	}

}

void task4_5::solution::take_extreme( data_type::const_iterator ut ) 
{
	if( ut->empty() )
		return;

	int max, min;
	max = min = ut->front();

	for( data_row::const_iterator it = ut -> cbegin() ; it != ut -> cend(); it++ )
	{
		min = std::min( min, *it );
		max = std::max( max, *it );	
	}
	boost::mutex::scoped_lock lock( mtx );
	{
		extreme.push_back( max );
		extreme.push_back( min );
	}
}

int task4_5::solution::get_min() const
{
	return _min;
}
int task4_5::solution::get_max() const
{
	return _max;
}
