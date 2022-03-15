// -----------------------------------------------------------------------------
#ifndef Command_H
#define Command_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <memory>
#include "std_lib_facilities.h" // found in p&p repo

// -----------------------------------------------------------------------------

class ICommand
{
public:
	ICommand() = default;
	virtual ~ICommand() {};
	virtual void execute() = 0;
	const virtual string getName() const = 0;
};

// -----------------------------------------------------------------------------

class IOnOffCommand
{
public:
	IOnOffCommand() : mIsOn(false) {}
	virtual ~IOnOffCommand() {};

	void toggleOnOff()
	{
		if (mIsOn)
		{
			mIsOn = false;
			off();
		}
		else
		{
			mIsOn = true;
			on();
		}
	}

	const virtual string& getName() const = 0;

protected:
	virtual void on() = 0;
	virtual void off() = 0;

private:
	bool mIsOn;
};

// -----------------------------------------------------------------------------

class IOnOffCommandableObject
	: public IOnOffCommand
{
public:
	IOnOffCommandableObject(string pObjectName)
		: mObjectName(pObjectName)
	{}

	virtual ~IOnOffCommandableObject() {};

	const virtual string& getName() const override { return mObjectName; }

protected:
	void on() override { cout << mObjectName << " on." << endl; }
	void off() override { cout << mObjectName <<" off." << endl; }

	string mObjectName;
};

// -----------------------------------------------------------------------------

class NoCommand
	: public ICommand
{
public:
	NoCommand()
	{}

	void execute() override { cout << "...nothing happened." << endl; }
	const string getName() const override { return "No Command."; }
};

// -----------------------------------------------------------------------------

class Light
	: public IOnOffCommandableObject
{
public:
	Light(string pLightName)
		: IOnOffCommandableObject(pLightName)
	{}
};

// -----------------------------------------------------------------------------

class LightCommand
	: public ICommand
{
public:
	LightCommand(Light* pLight) 
		: mLight(pLight) 
	{}
	
	// the class assumes that the light pointer will be cleaned up elsewhere...

	void execute() override 
	{ 
		mLight->toggleOnOff();
	}

	const string getName() const override { return mLight->getName(); }

private:
	Light* mLight;
};

// -----------------------------------------------------------------------------

class Stereo
	: public IOnOffCommandableObject
{
public:
	Stereo(string pStereoName, int pVolume)
		: IOnOffCommandableObject(pStereoName)
		, mCD("Empty")
		, mRadioStation("BBC Radio 4")
		, mVolume(pVolume)
	{}

	void setCD(string pCD) 
	{ 
		mCD = pCD; 
		cout << "Now playing: " << mCD << endl;
	}

	void setRadio(string pRadioStation) 
	{ 
		mRadioStation = pRadioStation; 
		cout << "Now listening to: " << mRadioStation << endl;
	}

	void setVolume(int pVolume) { mVolume = pVolume; }

protected:
	string mCD;
	string mRadioStation;
	int mVolume;
};

// -----------------------------------------------------------------------------

class StereoWithAutoCD
	: public Stereo
{
public:
	StereoWithAutoCD(string pStereoName, int pVolume, string pCD)
		: Stereo(pStereoName, pVolume)
	{
		mCD = pCD;
	}

protected:
	void on() override
	{
		Stereo::on();	// call super
		cout << "Now playing: " << mCD << " at " << mVolume << " volume." << endl;
	} 	
};

// -----------------------------------------------------------------------------

class StereoCommand
	: public ICommand
{
public:
	StereoCommand(Stereo* pStereo)
		: mStereo(pStereo)
	{}

	// the class assumes that the stereo pointer will be cleaned up elsewhere...

	void execute() override
	{
		mStereo->toggleOnOff();
	}

	const string getName() const override { return mStereo->getName(); }

private:
	Stereo* mStereo;
};

// -----------------------------------------------------------------------------

class SimpleRemoteControl
{
public:
	SimpleRemoteControl() {}
	~SimpleRemoteControl()
	{
		if (mCommandSlot)
		{
			delete mCommandSlot;
		}
	}

	void setCommand(ICommand* pCommand)
	{
		mCommandSlot = pCommand;
	}

	void onButtonPress() const
	{
		mCommandSlot->execute();
	}

	ICommand* mCommandSlot;
};

// -----------------------------------------------------------------------------

class ComplexRemoteControl
{
public:
	ComplexRemoteControl(const int pMaxNumCommands)
		: mCommands(pMaxNumCommands, nullptr)
	{
		for (int i = 0; i < pMaxNumCommands; ++i)
		{
			mCommands[i] = new NoCommand();
		}
	}

	~ComplexRemoteControl()
	{
		for (uint32 i = 0; i < mCommands.size(); ++i)
		{
			if (mCommands[i])
			{
				delete mCommands[i];
			}
		}
	}

	void setCommand(int pSlot, ICommand* pCommand)
	{
		if (pSlot >= mCommands.size() || pSlot < 0)
		{
			cout << "Error: Could not set command. The slot number " << pSlot
				<< "Is outside the ranges of 0 - " << mCommands.size()-1 << endl;
		}

		delete mCommands[pSlot];
		mCommands[pSlot] = pCommand;
	}

	void onButtonPressed(int pSlot) const
	{
		if (pSlot >= mCommands.size() || pSlot < 0)
		{
			cout << "Error: Command does not exist. The slot number " << pSlot
				<< "Is outside the ranges of 0 - " << mCommands.size() - 1 << endl;
		}
		else
		{	
			mCommands[pSlot]->execute();
		}
	}

	void printCommandSlots() const
	{
		cout << "\n---- Remote Control ----\n";
		for (uint32 i = 0; i < mCommands.size(); ++i)
		{
			cout << "Slot " << i << ": " << mCommands[i]->getName() << endl;
		}
		cout << endl;
	}

	vector<ICommand*> mCommands;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Command_H
