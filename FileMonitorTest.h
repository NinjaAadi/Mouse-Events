#pragma once
#include "Monitor.h"
#include <string>
#include "Test.h"
/*
	Type: File monitor class
	Description: Handle files from windowHandle
*/
class FileMonitorTest : TestInterface {
public:
	static void runTests();

private:
	static bool testMonitor();
	static bool testConstructor();

};