#pragma once


#pragma once
#include "Monitor.h"
#include <string>
#include "Test.h"
/*
	Type: Item monitor test class
	Description: Item monitor test class
*/
class ItemMonitorTest : TestInterface {
public:
	static void runTests();

private:
	static bool testMonitor();
	static bool testConstructor();

};