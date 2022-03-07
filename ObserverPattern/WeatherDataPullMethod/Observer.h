// -----------------------------------------------------------------------------
#ifndef Observer_H
#define Observer_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h" // found in p&p repo

// -----------------------------------------------------------------------------

class Observer
{
public:
	virtual void update() = 0;
};

// -----------------------------------------------------------------------------

class SubjectInterface
{
public:
	virtual void registerObserver(Observer* pObserver) = 0;
	virtual void removeObserver(Observer* pObserver) = 0;
	virtual void notifyObservers() = 0;
};

// -----------------------------------------------------------------------------

class DisplayElementInterface
{
public:
	virtual void display() = 0;
};

// -----------------------------------------------------------------------------

// WeatherData holds pointers to Observers, but it does not handle newing/deleting
// of Observer memory. Observers must handle themselves on destruction
class WeatherData
	: public SubjectInterface
{
public:
	WeatherData()
		: mObservers()
		, mTemperature(.0f)
		, mHumidity(.0f)
		, mPressure(.0f)
	{}

	// Begin SubjectInterface
	void registerObserver(Observer* pObserver)
	{
		mObservers.push_back(pObserver);
	}

	void  removeObserver(Observer* pObserver)
	{
		auto it = std::find(mObservers.begin(), mObservers.end(), pObserver);
		if (it == mObservers.end())
		{
			cout << "No observer found" << endl;
		}
		else
		{
			mObservers.erase(it);
		}
	}

	void notifyObservers()
	{
		for (Observer* o : mObservers)
		{
			o->update();
		}
	}
	// End SubjectInterface

	void measurementsChanged() { notifyObservers(); }
	void setMeasurements(float pTemp, float pHumidity, float pPressure)
	{
		mTemperature = pTemp;
		mHumidity = pHumidity;
		mPressure = pPressure;
		measurementsChanged();
	}

	const float getTemperature() const { return mTemperature; }
	const float getHumidity() const { return mHumidity; }
	const float getPressure() const { return mPressure; }

private:
	vector<Observer*> mObservers;
	float mTemperature;
	float mHumidity;
	float mPressure;
};

// -----------------------------------------------------------------------------

class CurrentConditionsDisplay
	: public DisplayElementInterface
	, public Observer
{
public:
	CurrentConditionsDisplay(WeatherData* pWeatherData)
		: mWeatherData(pWeatherData)
		, mTemperature(.0f)
		, mHumidity(.0f)
	{
		if (mWeatherData)
		{
			mWeatherData->registerObserver(this);
		}
		else
		{
			cout << "The WeatherData is not valid. Cannot register with it for Current updates." << endl;
		}
	}

	~CurrentConditionsDisplay()
	{
		mWeatherData->removeObserver(this);
	}

	// Begin DisplayElementInterface implementation
	void display()
	{
		cout << "Current Conditions: " << mTemperature << " F degrees and " << mHumidity
			<< "% humidity" << endl;
	}
	// End DisplayElementInterface implementation

	// Begin Observer implementation
	void update()
	{
		mTemperature = mWeatherData->getTemperature();
		mHumidity = mWeatherData->getHumidity();
		display();
	}
	// End Observer implementation

private:
	WeatherData* mWeatherData;
	float mTemperature;
	float mHumidity;
};

// -----------------------------------------------------------------------------

class ForecastDisplay
	: DisplayElementInterface
	, Observer
{
public:
	ForecastDisplay(WeatherData* pWeatherData)
		: mWeatherData(pWeatherData)
		, mCurrentPressure(29.920f)
		, mLastPressure(.0f)
	{
		if (mWeatherData)
		{
			mWeatherData->registerObserver(this);
		}
		else
		{
			cout << "The WeatherData is not valid. Cannot register with it for Forecast updates." << endl;
		}
	}

	~ForecastDisplay()
	{
		mWeatherData->removeObserver(this);
	}

	// Begin DisplayElementInterface implementation
	void display()
	{
		cout << "Forecast: ";
		if (mCurrentPressure > mLastPressure)
		{
			cout << "Improving weather on the way!" << endl;
		}
		else if (mCurrentPressure == mLastPressure)
		{
			cout << "More of the same." << endl;
		}
		else if (mCurrentPressure < mLastPressure)
		{
			cout << "Watch out for cooler, rainy weather." << endl;
		}
	}
	// End DisplayElementInterface implementation

	// Begin Observer implementation
	void update()
	{
		mLastPressure = mCurrentPressure;
		mCurrentPressure = mWeatherData->getPressure();
		display();
	}
	// End Observer implementation

private:
	WeatherData* mWeatherData;
	float mCurrentPressure;
	float mLastPressure;
};

// -----------------------------------------------------------------------------

class StatisticsDisplay
	: DisplayElementInterface
	, Observer
{
public:
	StatisticsDisplay(WeatherData* pWeatherData)
		: mWeatherData(pWeatherData)
		, mMaxTemp(.0f)
		, mMinTemp(200.0f)
		, mTempSum(.0f)
		, mNumReadings(0)
	{
		if (mWeatherData)
		{
			mWeatherData->registerObserver(this);
		}
		else
		{
			cout << "The WeatherData is not valid. Cannot register with it for Statistics updates." << endl;
		}
	}

	~StatisticsDisplay()
	{
		mWeatherData->removeObserver(this);
	}

	// Begin DisplayElementInterface implementation
	void display()
	{
		cout << "Avg: " << (mTempSum / mNumReadings)
			 << "  |  Max: " << mMaxTemp
			 << "  |  Min: " << mMinTemp << endl;
	}
	// End DisplayElementInterface implementation

	// Begin Observer implementation
	void update()
	{
		const float temp = mWeatherData->getTemperature();
		mTempSum += temp;
		++mNumReadings;

		if (temp > mMaxTemp)
		{
			mMaxTemp = temp;
		}
		else if (temp < mMinTemp)
		{
			mMinTemp = temp;
		}

		display();
	}
	// End Observer implementation

private:
	WeatherData* mWeatherData;
	float mMaxTemp;
	float mMinTemp;
	float mTempSum;
	int mNumReadings;
};

// -----------------------------------------------------------------------------

class HeatIndexDisplay
	: DisplayElementInterface
	, Observer
{
public:
	HeatIndexDisplay(WeatherData* pWeatherData)
		: mWeatherData(pWeatherData)
		, mHeatIndex(.0f)
	{
		if (mWeatherData)
		{
			mWeatherData->registerObserver(this);
		}
		else
		{
			cout << "The WeatherData is not valid. Cannot register with it for Statistics updates." << endl;
		}
	}

	~HeatIndexDisplay()
	{
		mWeatherData->removeObserver(this);
	}

	// Begin DisplayElementInterface implementation
	void display()
	{
		cout << "Heat Index: " << mHeatIndex << endl;
	}
	// End DisplayElementInterface implementation

	// Begin Observer implementation
	void update()
	{
		mHeatIndex = computeHeatIndex(mWeatherData->getTemperature(), mWeatherData->getHumidity());
		display();
	}
	// End Observer implementation

private:
	// t = temperature, rh = relative humidity
	float computeHeatIndex(float t, float rh)
	{
		float index = (float)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh)
			+ (0.00941695 * (t * t)) + (0.00728898 * (rh * rh))
			+ (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
			(0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 *
				(rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) +
			(0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +
			0.000000000843296 * (t * t * rh * rh * rh)) -
			(0.0000000000481975 * (t * t * t * rh * rh * rh)));
		return index;
	}

	WeatherData* mWeatherData;
	float mHeatIndex;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Observer_H
