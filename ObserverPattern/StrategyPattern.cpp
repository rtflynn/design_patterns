#include "pch.h"
#include <iostream>
#include "duck.h"

int main()
{
	Duck* someMallard = new Mallard;
	Duck* anotherDuck = new RubberDuck;

	std::cout << "Mallard:\n";
	someMallard->swim();
	someMallard->performFly();
	someMallard->performQuack();
	std::cout << "\n\n";
	std::cout << "Rubber Duck:\n";
	anotherDuck->swim();
	anotherDuck->performFly();
	anotherDuck->performQuack();
	/*
	Thanks to the fact that the fly and quack methods are now instance
	variables in the Duck class, we can change these on the fly, as
	the following few lines demonstrate.
	*/
	std::cout << "\n\nGiving the rubber duck a rocket!\n\n";
	anotherDuck->setFlyBehavior(new FlyWithRocket);
	anotherDuck->swim();
	anotherDuck->performFly();
	anotherDuck->performQuack();
}