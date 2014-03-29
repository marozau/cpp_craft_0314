#include "good_duck.hpp"

using namespace class_design::strategy;
int main()
{	
	fly_behavior* fb = new fly_with_wings(); // change object to change my_duck::perform_fly() behaviour
	quack_behavior* qb = new quack(); // change object to change my_duck::perform_quack() behaviour

	duck* my_duck = new mallard_duck( fb, qb );

	my_duck->perform_fly();
	my_duck->perform_quack();
	my_duck->swim();
	my_duck->display();

	return 0;
}