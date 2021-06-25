#pragma once
#include "iostream"

/*
Compiler warnings were pretty annoying here; apparently we need
to be somewhat careful when instantiating objects from an
abstract class.  The trick is to never declare such an object
directly, but rather use pointers.

Now that I think about it, this is also how polymorphism is
accomplished with things like std::vector<SomeBaseClass*>.
That is, use SomeBaseClass*, not SomeBaseClass.
*/


/*
Abstract class for quacking behavior.  Ducks (and perhaps other things) will
each have a quacking behavior, i.e. an instance variable of type QuackBehavior,
i.e. a concrete QuackBehavior.  Ducks will quack through polymorphism, using
their QuackBehavior's quack method.  Note, we can easily switch out behaviors
on any Duck object without needing to fiddle with any of the
quack-implementing code.
*/
class QuackBehavior {
public:
	virtual void quack() = 0;
};

class Quack : public QuackBehavior {
	void quack() override { std::cout << "Quack!\n"; };
};

class Squeek : public QuackBehavior {
	void quack() override { std::cout << "Squeek!\n"; };
};

class MuteQuack : public QuackBehavior {
	void quack() override { std::cout << "<<silence>>\n"; };
};

/*
Similar to QuackBehavior in spirit.  We pulled out the quack and flying behaviors
and rely on polymorphism instead of inheritance.  That is, we could have done this
differently, with the Duck class having fly() and quack() methods.  Then every
subclass would already have these behaviors. Some issues brought up in the design
patterns book include:
 - Some ducks shouldn't fly, such as rubber ducks
 - Ducks quack differently, so we'd have to overwrite quack() in many subclasses
  - Even if some ducks quack the same as each other, we'd have to repeat the
    implementing code each time.
 - We're writing to an implementation rather than to an interface.  This isn't
   always a bad thing, but it is in this case.  Generally, writing to an
   interface provides more flexibility in our programs.
*/
class FlyBehavior {
public:
	FlyBehavior() {};
	virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior {
	void fly() override {
		std::cout << "I'm flying with wings!\n";
	};
};

class FlyWithRocket : public FlyBehavior {
	void fly() override {
		std::cout << "I'm flying with a rocket pack!\n";
	};
};

class FlyNoWay : public FlyBehavior {
	void fly() override {};
};


/*
The Duck class will have some instance variables which all ducks should have, such
as weight and height.  We have taken the behaviors that differ between ducks, such
as quacking and flying, and turned these behaviors into objects.  Thus behaviors
can also be encapsulated as instance variables. This opens us up to some interesting
possibilities, such as dynamically changing a Duck's flying behavior.
*/
class Duck {
public:
	Duck(QuackBehavior* qb = nullptr, FlyBehavior* fb = nullptr) : quackBehavior(qb), flyBehavior(fb) {};
	~Duck() { delete quackBehavior; delete flyBehavior; }
	void performFly() {	flyBehavior->fly(); };
	void performQuack() { quackBehavior->quack(); };
	void swim() { std::cout << "All ducks swim!\n";	};
	void setFlyBehavior(FlyBehavior* fb) {
		if (flyBehavior != nullptr) delete flyBehavior;
		flyBehavior = fb;
	};
	void setQuackBehavior(QuackBehavior* qb) {
		if (quackBehavior != nullptr) delete quackBehavior;
		quackBehavior = qb;
	}
protected:
public:
	QuackBehavior* quackBehavior;
	FlyBehavior* flyBehavior;
};


class Mallard : public Duck {
public:
	Mallard() : Duck(new Quack, new FlyWithWings) {};
};

class RubberDuck : public Duck {
public:
	RubberDuck() : Duck(new Squeek, new FlyNoWay) {};
};

class FireworkDuck : public Duck {
public:
	FireworkDuck() : Duck(new MuteQuack, new FlyWithRocket) {};
};