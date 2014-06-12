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
		return x_;
	}

	int Y() const
	{
		return y_;
	}

	map_point_t(): x_( 0 ), y_( 0 )
	{
	}

	map_point_t( const int x, const int y ): x_( x ), y_( y )
	{
	}

	map_point_t up()
	{
		return map_point_t( x_, y_ - 1 );
	}

	map_point_t down()
	{
		return map_point_t( x_, y_ + 1 );
	}

	map_point_t right()
	{
		return map_point_t( x_ + 1, y_ );
	}

	map_point_t left()
	{
		return map_point_t( x_ - 1, y_ );
	}

private:
	int x_;
	int y_;
};

class map_t
{
public:

	map_t( istream& is )
	{
		string s;
		while( getline( is, s ) )
		{
			map_.push_back( s );
		}

		height_ = static_cast<int>( map_.size() );
		width_ = static_cast<int>( map_[ 0 ].length() );
	}

	int width() const
	{
		return width_;
	}

	int height() const
	{
		return height_;
	}

	bool is_earth( int x, int y ) const
	{
		return is_earth( map_point_t( x, y ) );
	}

	bool is_earth( map_point_t p ) const
	{
		return !( is_outside( p ) || map_[ p.Y() ][ p.X() ] != earth );
	}

	void set_visited( map_point_t p )
	{
		map_[ p.Y() ][ p.X() ] = visited;
	}

private:

	const char water = '~';
	const char earth = 'o';
	const char visited = '.';

	vector<string> map_;

	int width_;
	int height_;

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
