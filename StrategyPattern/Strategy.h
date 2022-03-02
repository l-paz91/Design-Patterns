// -----------------------------------------------------------------------------
#ifndef Practice_H
#define Practice_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <iostream>
using namespace std;

// -----------------------------------------------------------------------------

class I_FlyBehaviour
{
public:
	virtual void fly()
	{
		cout << "Default behaviour" << endl;
	}
};

// -----------------------------------------------------------------------------

class FlyWithWingsBehaviour
	: public I_FlyBehaviour
{
public:
	void fly() override
	{
		cout << "I'm flying!!" << endl;
	}
};

// -----------------------------------------------------------------------------

class NoFlightBehaviour
	: public I_FlyBehaviour
{
public:
	void fly() override
	{
		cout << "I can't fly" << endl;
	}
};

// -----------------------------------------------------------------------------

class RocketFlightBehaviour
	: public I_FlyBehaviour
{
public:
	void fly() override
	{
		cout << "I'm flying with a rocket!" << endl;
	}
};

// -----------------------------------------------------------------------------

class I_QuackBehaviour
{
public:
	virtual void quack()
	{
		cout << "Default behaviour" << endl;
	}
};

// -----------------------------------------------------------------------------

class NormalQuackBehaviour
	: public I_QuackBehaviour
{
public:
	void quack() override
	{
		cout << "Quack" << endl;
	}
};

// -----------------------------------------------------------------------------

class SilentQuackBehaviour
	: public I_QuackBehaviour
{
public:
	void quack() override
	{
		cout << "<< Silence >>" << endl;
	}
};

// -----------------------------------------------------------------------------

class SqueakQuackBehaviour
	: public I_QuackBehaviour
{
public:
	void quack() override
	{
		cout << "Squeak" << endl;
	}
};

// -----------------------------------------------------------------------------

class Duck
{
public:
	Duck(I_FlyBehaviour* pFlyType, I_QuackBehaviour* pQuackType)
		: mFlyBehaviour(pFlyType)
		, mQuackBehaviour(pQuackType)
	{}

	virtual ~Duck()
	{
		if (mFlyBehaviour)
		{
			delete mFlyBehaviour;
		}

		if (mQuackBehaviour)
		{
			delete mQuackBehaviour;
		}
	}

	virtual void display() {}

	void takeFlight() { mFlyBehaviour->fly(); }
	void makeNoise()  { mQuackBehaviour->quack(); }
	void swim()		  { cout << "All ducks float, even decoys!!" << endl; }

	void setFlyBehaviour(I_FlyBehaviour* pFlyType)
	{
		if (pFlyType && mFlyBehaviour)
		{
			delete mFlyBehaviour;
			mFlyBehaviour = pFlyType;
		}
		else
		{
			cout << "Fly behaviour was not valid." << endl;
		}
	}

	void setQuackBehaviour(I_QuackBehaviour* pQuackType)
	{
		if(pQuackType && mQuackBehaviour)
		{
			delete mQuackBehaviour;
			mQuackBehaviour = pQuackType;
		}
		else
		{
			cout << "Quack behaviour was not valid." << endl;
		}
	}

private:
	I_FlyBehaviour* mFlyBehaviour;
	I_QuackBehaviour* mQuackBehaviour;
};

// -----------------------------------------------------------------------------

class MallardDuck 
	: public Duck
{
public:
	MallardDuck()
		: Duck(new FlyWithWingsBehaviour(), new NormalQuackBehaviour())
	{}
	
	void display() override { cout << "I'm a real Mallard duck" << endl; }
};

// -----------------------------------------------------------------------------

class ModelDuck
	: public Duck
{
public:
	ModelDuck()
		: Duck(new NoFlightBehaviour(), new NormalQuackBehaviour())
	{}

	void display() override { cout << "I'm a model duck" << endl; }
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Practice_H
