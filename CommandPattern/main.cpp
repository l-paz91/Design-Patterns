// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Head First Design Patterns (2nd Ed.)

	Chapter 6 - Command Pattern

	Note - This book uses Java. I have adapted the code samples given in the book
	to use C++ instead.

	I changed this from the book and added some more interfaces. it is very OOP now
	and I hate it with a passion. It feels a lot like the strategy pattern but we
	use this extensively at work. Especially as UE4 is practically Interface Engine 4.

*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Command.h"

// -----------------------------------------------------------------------------

void testSimpleRemoteControl()
{
	// objects
	Light cornerLamp("Corner Lamp");

	SimpleRemoteControl remoteControl;
	remoteControl.setCommand(new LightCommand(&cornerLamp));
	remoteControl.onButtonPress();
	remoteControl.onButtonPress();
	remoteControl.onButtonPress();
}

// -----------------------------------------------------------------------------

void testComplexRemoteControl()
{
	// objects
	Light cornerLamp("Corner Lamp");
	Light wallLamp("Wall Lamp");

	Stereo kitchenStereo("Kitchen Stereo", 5);
	StereoWithAutoCD hallwayStereo("Hallway Stereo", 11, "James Blunt - Back to Bedlam");

	ComplexRemoteControl remoteControl(4);
	remoteControl.printCommandSlots();

	remoteControl.setCommand(0, new LightCommand(&cornerLamp));
	remoteControl.setCommand(1, new LightCommand(&wallLamp));
	remoteControl.setCommand(2, new StereoCommand(&kitchenStereo));
	remoteControl.setCommand(3, new StereoCommand(&hallwayStereo));

	remoteControl.printCommandSlots();

	remoteControl.onButtonPressed(0);
	remoteControl.onButtonPressed(0);
	remoteControl.onButtonPressed(0);
	remoteControl.onButtonPressed(1);
	remoteControl.onButtonPressed(1);
	remoteControl.onButtonPressed(1);
	remoteControl.onButtonPressed(2);
	remoteControl.onButtonPressed(2);
	remoteControl.onButtonPressed(2);
	remoteControl.onButtonPressed(3);
	remoteControl.onButtonPressed(3);
	remoteControl.onButtonPressed(3);
}

// -----------------------------------------------------------------------------

int main()
{
	// done to keep an eye on memory tracking (it will always report as a leak if done in main)
	testSimpleRemoteControl();
	testComplexRemoteControl();

	pressKeyToContinue();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
