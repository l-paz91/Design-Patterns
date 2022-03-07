// -----------------------------------------------------------------------------
#ifndef Decorator_H
#define Decorator_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <memory>
#include "std_lib_facilities.h" // found in p&p repo

// -----------------------------------------------------------------------------

class Beverage
{
public:
	Beverage(string pName = "Default Beverage") : mDescription(pName) {}

	virtual ~Beverage()
	{
		cout << "Destroying " << getDesc() << endl;
	}

	virtual const string getDesc() const { return mDescription; }
	virtual		      double cost() const { return 0; }

	string mDescription;
};

// -----------------------------------------------------------------------------

class CondimentDecorator
	: public Beverage
{
public:
	CondimentDecorator(unique_ptr<Beverage> pBeverage)
		: mBeverage(std::move(pBeverage))
	{}

	virtual ~CondimentDecorator()
	{
		cout << "Destroying " << getDesc() << endl;
	}

	const string getDesc() const override { return "CondimentDecorator"; }

	unique_ptr<Beverage> mBeverage;
};

// -----------------------------------------------------------------------------

class Espresso
	: public Beverage
{
public:
	Espresso()
		: Beverage("Espresso")
	{}

	double cost() const override { return 1.99; }
};

// -----------------------------------------------------------------------------

class HouseBlend
	: public Beverage
{
public:
	HouseBlend()
		: Beverage("House Blend Coffee")
	{}

	double cost() const override { return 0.89; }
};

// -----------------------------------------------------------------------------

class DarkRoast
	: public Beverage
{
public:
	DarkRoast()
		: Beverage("Dark Roast Coffee")
	{}

	double cost() const override { return 0.99; }
};

// -----------------------------------------------------------------------------

class Decaf
	: public Beverage
{
public:
	Decaf()
		: Beverage("Decaf Coffee")
	{}

	double cost() const override { return 1.05f; }
};

// -----------------------------------------------------------------------------

class Mocha
	: public CondimentDecorator
{
public:
	Mocha(unique_ptr<Beverage> pBeverage)
		: CondimentDecorator(std::move(pBeverage))
	{
		mDescription = "Mocha";
	}

	const string getDesc() const override
	{
		stringstream ss;
		ss << mBeverage->getDesc() << ", Mocha";
		return ss.str();
	}
		
	double cost() const override 
	{
		return mBeverage->cost() + 0.20; 
	}
};

// -----------------------------------------------------------------------------

class SteamedMilk
	: public CondimentDecorator
{
public:
	SteamedMilk(unique_ptr<Beverage> pBeverage)
		: CondimentDecorator(std::move(pBeverage))
	{
		mDescription = "Steamed Milk";
	}

	const string getDesc() const override
	{
		stringstream ss;
		ss << mBeverage->getDesc() << ", Steamed Milk";
		return ss.str();
	}

	double cost() const override
	{
		return mBeverage->cost() + 0.10;
	}
};

// -----------------------------------------------------------------------------

class Soy
	: public CondimentDecorator
{
public:
	Soy(unique_ptr<Beverage> pBeverage)
		: CondimentDecorator(std::move(pBeverage))
	{
		mDescription = "Soy";
	}

	const string getDesc() const override
	{
		stringstream ss;
		ss << mBeverage->getDesc() << ", Soy Milk";
		return ss.str();
	}

	double cost() const override
	{
		return mBeverage->cost() + 0.15;
	}
};

// -----------------------------------------------------------------------------

class Whip
	: public CondimentDecorator
{
public:
	Whip(unique_ptr<Beverage> pBeverage)
		: CondimentDecorator(std::move(pBeverage))
	{
		mDescription = "Whip";
	}

	const string getDesc() const override
	{
		stringstream ss;
		ss << mBeverage->getDesc() << ", Whipped Cream";
		return ss.str();
	}

	double cost() const override
	{
		return mBeverage->cost() + 0.10;
	}
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Decorator_H
