// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Taken from: Head First Design Patterns (2nd Ed.)

	Chapter 1 - Strategy Pattern

	The Strategy Pattern defines a family of algorithms, encapsulates each one,
	and makes them interchangeable. Strategy lets the algorithm vary independently
	from clients that use it.

	Note - This book uses Java. I have adapted the code samples given in the book
	to use C++ instead.
*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Strategy.h"


//--GLOBALS--//

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

void fct()
{
	Duck* mallardDuck = new MallardDuck();
	mallardDuck->makeNoise();
	mallardDuck->takeFlight();

	cout << "-------------------------\n";

	Duck* modelDuck = new ModelDuck();
	modelDuck->takeFlight();
	modelDuck->setFlyBehaviour(new RocketFlightBehaviour());
	modelDuck->takeFlight();

	delete modelDuck;
	delete mallardDuck;
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
