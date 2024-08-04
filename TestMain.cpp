#include "WindowTest.h"
#include "HookServiceTest.h"
#include "MouseCoordinatesTest.h"
#include "FileMonitorTest.h"
#include "ItemMonitorTest.h"


void testMain() {
	WindowTest::runTests();
	HookServiceTest::runTests();
	FileMonitorTest::runTests();
	ItemMonitorTest::runTests();
	MouseCoordinatesTest::runTests();
}