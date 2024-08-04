#include "HookServiceTest.h"
#include "MouseCoordinates.h"

/*
	Type: Hook service Test class implementation
	Description: Contains implementation function for HookServiceTest class
*/
void HookServiceTest::runTests() {
	std::cout << "Running test cases for  Hook Service class...\n";
	if (testSetHook() &&
		testUnHook()) {

		std::cout << "Test case passed successfully\n";
	}
	else {

		std::cout << "Test case failed\n";
	}
}

bool HookServiceTest::testUnHook(){
	MouseCoordinates mouseCoordinates = MouseCoordinates();
	mouseCoordinates.setHook();
	mouseCoordinates.unHook();
	if (mouseCoordinates.getHook() != NULL) {

		std::cout << "Test failed: unHook\n";
		mouseCoordinates.unHook();
		return false;
	}
	else {
		std::cout << "Test passed: unHook\n";
		mouseCoordinates.unHook();
		return true;
	}
}


bool HookServiceTest::testSetHook() {
	MouseCoordinates mouseCoordinates = MouseCoordinates();
	mouseCoordinates.setHook();

	if (mouseCoordinates.getHook() == NULL) {

		std::cout << "Test failed: setHook\n";
		mouseCoordinates.unHook();
		return false;
	}
	else {
		std::cout << "Test passed: setHook\n";
		mouseCoordinates.unHook();
		return true;
	}
}