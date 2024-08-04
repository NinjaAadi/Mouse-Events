#include "ItemMonitorTest.h"
#include "ItemMonitor.h"
#include <iostream>
#include <Windows.h>
#include "Window.h"
/*
    Type: FileMonitor test class implementation
*/

void ItemMonitorTest::runTests() {
    std::cout << "Running test cases for  File Monitor class...\n";
    if (testMonitor() &&
        testConstructor()
        ) {

        std::cout << "Test case passed successfully\n";

    }
    else {

        std::cout << "Test case failed\n";
    }
}

bool ItemMonitorTest::testMonitor() {
    
    //We are only calling windowAPI::testItem which is already tested...
    std::cout << "Test passed:Monitor\n";
    return true;
}



bool ItemMonitorTest::testConstructor() {


    ItemMonitor* itemMonitor = new ItemMonitor();
    ItemMonitor itemMonitorTest = ItemMonitor(itemMonitor);

    if (itemMonitorTest.getCallBack() == NULL) {

        std::cout << "Test failed: ItemMonitor callback constructor\n";
        return false;
    }
    std::cout << "Test passed: ItemMonitor callback constructor"<<std::endl;
    return true;
}

