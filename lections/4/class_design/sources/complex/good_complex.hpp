// 14
#ifndef _CLASS_DESIGN_COMPLEX_GOOD_COMPLEX_HPP_ 
#define _CLASS_DESIGN_COMPLEX_GOOD_COMPLEX_HPP_

#include <iostream>

namespace class_design
{
	namespace complex
	{
		// 1
		class complex 
		{
			// 11
			double real_;
			double imaginary_;

		public:
			// 2
			explicit complex( double real, double imaginary = 0 )
				: real_( real )
				, imaginary_( imaginary )
			{
			}
			// 3, 4
			complex& operator+=( const complex& other )
			{
				real_ += other.real_;
				imaginary_ += other.imaginary_;
				return *this;
			}
			// 9
			complex& operator++()
			{
				++real_;
				return *this;
			}
			// 7, 10,
			const complex operator++( int )
			{
				complex temp( *this );
				++*this;
				return temp;
			}
			// 8
			std::ostream& print( std::ostream& os ) const
			{
				return os << "(" << real_ << "," << imaginary_ << ")";
			}
		};
		// 3, 4, 5
		const complex operator+( const complex& lhs, const complex& rhs )
		{
			complex ret( lhs );
			ret += rhs;
			return ret;
		}
		// 5, 6(if no complex::print operation), 8
		std::ostream& operator<<( std::ostream& os, const complex& c )
		{
		return c.print( os );
		}

	}
}

#endif // _CLASS_DESIGN_COMPLEX_GOOD_COMPLEX_HPP_

