#include <iostream> 
#include <complex>

namespace class_design
{
	namespace inheritance
	{
		class base
		{
		public:
			// there is a base::f function overloading within the base scope 
			virtual void f( int ) { std::cout << "base::f( int )" << std::endl; } 
			virtual void f( double ) { std::cout << "base::f( double )" << std::endl; }
			virtual void g( int i = 10 ) { std::cout << "base::g() " << i <<std::endl; }
			virtual base& clone() 
			{
				return *this; 
			}
		};
		
		class derived: public base
		{
		public:			
			// write 'using base::f' to bring base::f to the derived scope
			void f( std::complex< double > ) { std::cout << "derived::f( complex )" << std::endl; } // it does not overload base::f so it hides base::f
			void g( int i = 20 ) { std::cout << "derived::g( int ) " << i << std::endl; } // overrides base::f
			virtual derived& clone() 
			{ 
				return *this; 
			}
		};
	}
}

using namespace class_design::inheritance;

// msvc compiles 'void main()' without warnings. Even though "void main()" is not one of the legal declarations of main.
void main()
{
	base b;
	derived d;
	base* pb = new derived;
	b.f(1.0);
	d.f(1.0);

	// as derived::f doesn't overload base::f overload resolution is done on the static type (here base), not the dynamic type (here derived).
	// "pb->f(complex<double>(1.0));"  would not compile
	pb->f(1.0); 

	b.g();
	d.g();

	// default parameters are taken from the static type ( here base )
	pb->g();

	// virtual methods overriding works although base::clone() and derivrd::clone have different return types
	pb->clone();

	// Deleting via a pointer-to-base without a virtual destructor leads to the memory corruption, 
	// because the wrong destructor will get called and operator delete() will be invoked with the wrong object size
	// Make base class destructors virtual (unless you are certain that no one will
	// ever attempt to delete a derived object through a pointer to base).
	delete pb;  

}