#pragma once
#include <Windows.h>
#include "Test.h"
class WindowTest : TestInterface {
public:
	static void runTests();

private:
	static bool testGetWindowFromPoint();
	static bool testGetProcessIDFromHWND();
	static bool testGetHandleFromProcessID();
	static bool testGetWindowClassNameFromHWND();
	static bool testGetExeFilePathFromHandle();
	static bool testCloseHandle();

};