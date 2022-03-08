// -----------------------------------------------------------------------------
#ifndef Factory_H
#define Factory_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <memory>
#include "std_lib_facilities.h" // found in p&p repo

// -----------------------------------------------------------------------------

class Pizza
{
public:
	Pizza(string pName, string pDough, string pSauce)
		: mToppings()
		, mName(pName)
		, mDough(pDough)
		, mSauce(pSauce)
	{}

	virtual ~Pizza() = default;

	virtual void prepare() const
	{
		cout << "Preparing " << mName;
		cout << "\nTossing dough...";
		cout << "\nAdding sauce...";
		cout << "\nAdding toppings: ";
		for (const string& s : mToppings)
		{
			cout << s << ", ";
		}
		cout << endl;
	}

	virtual void bake() const 
	{
		cout << "Bake for 25 minutes at 350" << endl;
	}

	virtual void cut() const
	{
		cout << "Cutting the pizza into diagonal slices" << endl;
	}

	virtual void box() const
	{
		cout << "Place pizza in official PizzaStore box" << endl;
	}

	const string& getName() const { return mName; }

	vector<string> mToppings;
	string mName;
	string mDough;
	string mSauce;
};

// -----------------------------------------------------------------------------

class PizzaStore
{
public:
	// I'm deliberately returning copies to avoid newing up data
	Pizza orderPizza(string pType)
	{
		Pizza pizza = createPizza(pType);
		pizza.prepare();
		pizza.bake();
		pizza.cut();
		pizza.box();
		return pizza;
	}

	virtual Pizza createPizza(string pType) = 0;
};

// -----------------------------------------------------------------------------

class NYStyleCheesePizza
	: public Pizza
{
public:
	NYStyleCheesePizza()
		: Pizza("NY Style Sauce and Cheese Pizza", "Thin Crust Dough", "Marinara Sauce")
	{
		mToppings.push_back("Grated Reggiano Cheese");
	}
};

// -----------------------------------------------------------------------------

class ChicagoStyleCheesePizza
	: public Pizza
{
public:
	ChicagoStyleCheesePizza()
		: Pizza("Chicago Style Deep Dish Cheese Pizza", "Extra Thick Crust Dough", "Plum Tomato Sauce")
	{
		mToppings.push_back("Shredded Mozzarella Cheese");
	}

	void cut() const override
	{
		cout << "Cutting the pizza into square slices." << endl;
	}
};

// -----------------------------------------------------------------------------

class NYPizzaStore
	: public PizzaStore
{
public:
	Pizza createPizza(string pType) override
	{
		if (pType == "cheese")
		{
			return NYStyleCheesePizza();
		}
	}
};

// -----------------------------------------------------------------------------

class ChicagoPizzaStore
	: public PizzaStore
{
public:
	Pizza createPizza(string pType) override
	{
		if (pType == "cheese")
		{
			return ChicagoStyleCheesePizza();
		}
	}
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Factory_H
