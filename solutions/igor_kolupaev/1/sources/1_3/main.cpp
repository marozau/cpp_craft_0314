#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class map_point_t
{
public:

	int X() const
	{
		return _x;
	}

	int Y() const
	{
		return _y;
	}

	map_point_t(): _x( 0 ), _y( 0 )
	{
	}

	map_point_t( const int x, const int y ): _x( x ), _y( y )
	{
	}

	map_point_t up()
	{
		return map_point_t( _x, _y - 1 );
	}

	map_point_t down()
	{
		return map_point_t( _x, _y + 1 );
	}

	map_point_t right()
	{
		return map_point_t( _x + 1, _y );
	}

	map_point_t left()
	{
		return map_point_t( _x - 1, _y );
	}

private:
	int _x;
	int _y;
};

class map_t
{
public:

	map_t( istream& is )
	{
		string s;
		while( getline( is, s ) )
		{
			_map.push_back( s );
		}

		_height = static_cast<int>( _map.size() );
		_width = static_cast<int>( _map[ 0 ].length() );
	}

	int width() const
	{
		return _width;
	}

	int height() const
	{
		return _height;
	}

	bool is_earth( int x, int y ) const
	{
		return is_earth( map_point_t( x, y ) );
	}

	bool is_earth( map_point_t p ) const
	{
		return !( is_outside( p ) || _map[ p.Y() ][ p.X() ] != earth );
	}

	void set_visited( map_point_t p )
	{
		_map[ p.Y() ][ p.X() ] = visited;
	}

private:

	const char water = '~';
	const char earth = 'o';
	const char visited = '.';

	vector<string> _map;

	int _width;
	int _height;

	bool is_outside( map_point_t p ) const
	{
		return
			p.Y() < 0 || p.Y() >= height() ||
			p.X() < 0 || p.X() >= width();
	}
};

void fill_island( map_t& map, map_point_t start_point )
{
	if( !map.is_earth( start_point ) )
	{
		return;
	}

	stack<map_point_t> points_to_visit;
	points_to_visit.push( start_point );

	while( !points_to_visit.empty() )
	{
		map_point_t p = points_to_visit.top();
		points_to_visit.pop();

		map.set_visited( p );

		if( map.is_earth( p.right() ) )
		{
			points_to_visit.push( p.right() );
		}

		if( map.is_earth( p.left() ) )
		{
			points_to_visit.push( p.left() );
		}

		if( map.is_earth( p.up() ) )
		{
			points_to_visit.push( p.up() );
		}

		if( map.is_earth( p.down() ) )
		{
			points_to_visit.push( p.down() );
		}
	}
}

int main( int argc, char* argv[] )
{
	ifstream input_file( BINARY_DIR "/input.txt" );

	if( !input_file.is_open() )
	{
		cerr << "Unable to open input.txt";
		return 1;
	}

	map_t map( input_file );

	input_file.close();

	int islands_count = 0;

	for( int y = 0; y < map.height(); ++y )
	{
		for( int x = 0; x < map.width(); ++x )
		{
			map_point_t p( x, y );

			if( map.is_earth( p ) )
			{
				++islands_count;
				fill_island( map, p );
			}
		}
	}

	ofstream output_file( BINARY_DIR "/output.txt" );
	output_file << islands_count << endl;
	output_file.close();
}
