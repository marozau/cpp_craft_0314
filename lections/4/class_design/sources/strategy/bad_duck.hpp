#ifndef _CLASS_DESIGN_STARTEGY_BAD_DUCK_HPP_
#define _CLASS_DESIGN_STARTEGY_BAD_DUCK_HPP_

#include <iostream>

// 1. Add new method 'void fly()'
// 2. New duck class 'rubbed_duck' with no method fly()

namespace class_design
{
	namespace strategy
	{
		// If you want to add new method to the bad_duck abstract class you should implement it in all the inherited classes.
		// To change swim() method behaviour you should create a new inherited class with new swim() implementation. 
		// All of this leads to the fast increase of code complexity and code duplication.
		class bad_duck
		{
		public:
			virtual ~bad_duck() {}
			virtual void quack() = 0;
			virtual void swim() = 0;
			virtual void display() = 0;
		};

		class bad_mallard_duck : public bad_duck
		{
		public:
			virtual void quack() { /* ... */ }
			virtual void swim() { /* ... */ }
			virtual void display() { /* ... */ }
		};

		class bad_redhead_duck : public bad_duck
		{
		public:
			virtual void quack() { /* ... */ }
			virtual void swim() { /* ... */ }
			virtual void display() { /* ... */ }
		};
	}
}

#endif // _CLASS_DESIGN_STARTEGY_BAD_DUCK_HPP_
