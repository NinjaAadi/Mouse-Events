#pragma once
#include<Windows.h>
#include<iostream>
#include "Test.h"


/*
	Type: Hook interface test
	Description: Each hook registered need to implement HookService
*/
class HookServiceTest : TestInterface {
public:
	static void runTests();
	
private: 
	static bool testUnHook();
	static bool testSetHook();
};

