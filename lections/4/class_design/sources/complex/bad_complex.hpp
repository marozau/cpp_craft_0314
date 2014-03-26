// 14
#include <iostream>

namespace class_design
{
	namespace complex
	{
		// 1 (slide number)
		class Complex 
		{
		public:
			// 2
			Complex( double real, double imaginary = 0 )
			: _real(real), _imaginary(imaginary)
			{
			}
			// 3, 4, 5
			void operator+( Complex other )
			{
				_real = _real + other._real;
				_imaginary = _imaginary + other._imaginary;
			}
			// 5, 6, 8
			void operator<<( std::ostream os )
			{
				os << "(" << _real << "," << _imaginary << ")";
			}
			// 7, 9
			Complex operator++()
			{
				++_real;
				return *this;
			}
			// 7, 10
			Complex operator++( int )
			{
				Complex temp = *this;
				++_real;
				return temp;
			}

		private:
			// 11
			double _real, _imaginary;
		};
	}
}


