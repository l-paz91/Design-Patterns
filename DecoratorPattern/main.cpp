// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Head First Design Patterns (2nd Ed.)

	Chapter 3 - Decorator Pattern

	Note - This book uses Java. I have adapted the code samples given in the book
	to use C++ instead.

	This pattern makes sense in a language with garbage collection, but in C++
	it's a potential memory leaking nightmare.

	Instead of using raw pointers (keeping track was giving me a headache), I used
	unique_ptr, std::move and virtual destructors to ensure all memory was freed
	up properly.

*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Decorator.h"

// -----------------------------------------------------------------------------

void fct()
{
	unique_ptr<Beverage> espresso = make_unique<Espresso>();
	cout << espresso->getDesc() << " $" << espresso->cost() << endl;

	unique_ptr<Beverage> darkRoast = make_unique<DarkRoast>();
	darkRoast = make_unique<Mocha>(std::move(darkRoast));
	darkRoast = make_unique<Mocha>(std::move(darkRoast));
	darkRoast = make_unique<Whip>(std::move(darkRoast));
	cout << darkRoast->getDesc() << " $" << darkRoast->cost() << endl;

	unique_ptr<Beverage> houseBlend = make_unique<HouseBlend>();
	houseBlend = make_unique<Soy>(std::move(houseBlend));
	houseBlend = make_unique<Mocha>(std::move(houseBlend));
	houseBlend = make_unique<Whip>(std::move(houseBlend));
	cout << houseBlend->getDesc() << " $" << houseBlend->cost() << endl;
}

// -----------------------------------------------------------------------------

int main()
{
	// done to keep an eye on memory tracking (it will always report as a leak if done in main)
	fct();

	pressKeyToContinue();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
