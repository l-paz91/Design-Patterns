// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Head First Design Patterns (2nd Ed.)

	Chapter 2 - Observer Pattern

	The Strategy Pattern defines a family of algorithms, encapsulates each one,
	and makes them interchangeable. Strategy lets the algorithm vary independently
	from clients that use it.

	Note - This book uses Java. I have adapted the code samples given in the book
	to use C++ instead.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Observer.h"


//--GLOBALS--//

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

void fct()
{
	WeatherData weatherData;

	CurrentConditionsDisplay currentConditions(&weatherData);
	StatisticsDisplay statisticsDisplay(&weatherData);
	ForecastDisplay forecastDisplay(&weatherData);
	HeatIndexDisplay heatIndexDisplay(&weatherData);

	weatherData.setMeasurements(80.f, 65.f, 30.4f);
	cout << "\n";
	weatherData.setMeasurements(82.f, 70.f, 29.2f);
	cout << "\n";
	weatherData.setMeasurements(78.f, 90.f, 29.2f);
	cout << endl;
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
