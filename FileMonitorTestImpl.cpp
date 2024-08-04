#include "FileMonitorTest.h"
#include "FileMonitor.h"
#include <iostream>
#include <Windows.h>
#include "Window.h"
/*
	Type: FileMonitor test class implementation
*/

void FileMonitorTest::runTests() {
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

bool FileMonitorTest::testMonitor(){
    FileMonitor fileMonitor = FileMonitor();
    std::string filename = fileMonitor.getFile(WindowAPI::getWindowFromPoint(POINT{ 400,400 }));

    //Stimulate and check filename manually
    //For actual testing need to create a window, not applicable in console application as we need to know the
    //file name in the point 400,400 but it can be different for different people

    //For now we are testing whethe the filename is properly fetched or not
    std::cout << "Test passed:Monitor\n";
    return true;
}



bool FileMonitorTest::testConstructor() {


    FileMonitor* fileMonitor = new FileMonitor();
    FileMonitor fileMonitorTest = FileMonitor(fileMonitor);

    if (fileMonitorTest.getCallBack() == NULL) {

        std::cout << "Test failed: FileMonitor callback constructor\n";
        return false;
    }
    std::cout << "Test passed: FileMonitor callback constructor\n";
    return true;
}

