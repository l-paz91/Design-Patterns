// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Head First Design Patterns (2nd Ed.)

	Chapter 4 - Factory Pattern

	Note - This book uses Java. I have adapted the code samples given in the book
	to use C++ instead.

	I found this example a bit odd but I see what they're getting at. 
*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Factory.h"

// -----------------------------------------------------------------------------

void fct()
{
	PizzaStore* nyStore = new NYPizzaStore();
	PizzaStore* chicagoStore = new ChicagoPizzaStore();

	Pizza nyPizza = nyStore->orderPizza("cheese");
	cout << "Ethan ordered a " << nyPizza.getName() << "\n" << endl;

	Pizza chicagoPizza = chicagoStore->orderPizza("cheese");
	cout << "Joel ordered a " << chicagoPizza.getName() << endl;

	delete nyStore;
	delete chicagoStore;
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
