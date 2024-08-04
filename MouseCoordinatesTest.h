#pragma once
#include "HookService.h"
#include <functional>
#include "Monitor.h"
#include "Test.h"

/*
    Type: Mouse coordinates  Test Class
  */
class MouseCoordinatesTest : TestInterface {
public:
    static void runTests();


private:
    static bool testConstructor();
    static bool testRegisterHook();
    static bool testUnregisterHook();
    static bool testHook();

};

