#include <iostream>

class a_class
{
	int a_;

public:
	explicit a_class() : a_( 10 ) {}
	a_class( const a_class& a ) : a_( a.a_ + 10 ) {
		std::cout << "copy constructor: " << a_ << std::endl;
	}
	const a_class& operator = ( a_class a ) 
	{
		a.a_ += 10;
		std::swap( a_, a.a_ ); 		
		std::cout << "assigment operator: " << a_ << std::endl;
		return *this;
	}
};

int main()
{
	a_class a;
	a_class a_copy = a;
	a_copy = a;

	return 0;
}