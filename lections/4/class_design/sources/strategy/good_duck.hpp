#ifndef _CLASS_DESIGN_STARTEGY_GOOD_DUCK_HPP_
#define _CLASS_DESIGN_STARTEGY_GOOD_DUCK_HPP_

#include <iostream>

namespace class_design
{
	namespace strategy
	{
		// interface for all object that do 'quack'
		// This class and all its nested classes are 'quack behavior' incapsulation
		class quack_behavior 
		{
		public:
			virtual ~quack_behavior() {}
			virtual void do_quack() = 0;
		};
		class quack : public quack_behavior
		{
		public:
			void do_quack() { std::cout << "quack" << std::endl; }
		};
		class mute_quack : public quack_behavior
		{
		public:
			void do_quack() { std::cout << "silence" << std::endl; }
		};
		//
		// interface for all object that do 'fly'
		// This class and all its nested classes are 'fly behavior' incapsulation
		class fly_behavior
		{
		public:
			virtual ~fly_behavior() {}
			virtual void do_fly() = 0;
		};
		class fly_with_wings : public fly_behavior
		{
		public:
			void do_fly() { std::cout << "fly!" << std::endl; }
		};
		class cant_fly : public fly_behavior
		{
		public:
			void do_fly() { std::cout << "can't fly" << std::endl; }
		};

		// abstract class for all ducks
		class duck
		{		
			fly_behavior* fb_; // composition
			quack_behavior* qb_; // composition

		public:
			explicit duck( fly_behavior* const fb, quack_behavior* const qb )
				: fb_( fb )
				, qb_( qb )
			{}
			virtual ~duck() 
			{
				delete fb_;
				delete qb_;
			}
			void perform_fly()
			{
				fb_->do_fly();
			}
			void perform_quack()
			{
				qb_->do_quack();
			}
			void swim()
			{
				std::cout << "all ducks can swim" << std::endl;
			}
			virtual void display() = 0;
		};
		class mallard_duck : public duck
		{
		public:
			explicit mallard_duck( fly_behavior* const fb, quack_behavior* const qb )
				: duck( fb, qb )
			{}
			virtual void display()
			{
				std::cout << "Hi! I'm mallard_duck! " << std::endl;
			}
		};
	}
}

#endif // _CLASS_DESIGN_STARTEGY_GOOD_DUCK_HPP_