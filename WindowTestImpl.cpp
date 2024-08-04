#pragma once
#include "WindowTest.h"
#include <iostream>
#include "Window.h"
/*
	Type: Window class test function implementations
	Description: Contains implementations of Window class functions
*/



void WindowTest::runTests() {
    std::cout << "Running test cases for Window class....\n";
    if (testGetWindowFromPoint() &&
        testGetProcessIDFromHWND() &&
        testGetHandleFromProcessID() &&
        testGetWindowClassNameFromHWND() &&
        testGetExeFilePathFromHandle() &&
        testCloseHandle()
     ) {
        std::cout<<"Test case passed successfully\n";
    }
    else {
        std::cout << "Test case failed\n";
    }
}



bool WindowTest::testGetWindowFromPoint() {
    //To test more more rigidly, we can create our own window for that.


    //Assuming there is an open window at point 400,400
    POINT pt = { 400, 400 }; 


    // Get the HWND from the point
    HWND hwndFromPoint = WindowAPI::getWindowFromPoint(pt);

    // Check if we got a valid HWND
    if (hwndFromPoint != NULL) {

        std::cout << "Test passed: getWindowFromPoint returned a valid HWND\n";
        return true;
    }
    else {
        std::cout << "Test failed: getWindowFromPoint returned NULL\n";
        return false;
    }

}



bool WindowTest::testGetProcessIDFromHWND() {

    POINT pt = { 400, 400 };
    HWND hwnd = WindowAPI::getWindowFromPoint(pt);
    DWORD processID = WindowAPI::getProcessIDFromHWND(hwnd);

    if (processID == 0) {

        std::cout << "Test failed: getProcessIDFromHWND\n";
        return false;
    }

    //Check when passed null
    processID = WindowAPI::getProcessIDFromHWND(NULL);
    if (processID != 0) {

        std::cout << "Test failed: getProcessIDFromHWND\n";
        return false;
    }
    std::cout << "Test passed: getProcessIDFromHWND\n";
    return true;

}



bool WindowTest::testGetHandleFromProcessID() {

    DWORD processID = GetCurrentProcessId();
    HANDLE handle = WindowAPI::getHandleFromProcessID(PROCESS_QUERY_INFORMATION, FALSE, processID);
    if (handle == NULL) {

        std::cout << "Test failed: getHandleFromProcessID\n";
        WindowAPI::closeHandle(handle);
        return false;
    }

    handle = WindowAPI::getHandleFromProcessID(FALSE, FALSE, NULL);


    if (handle != NULL) {
        std::cout << "Test failed: getHandleFromProcessID\n";
        WindowAPI::closeHandle(handle);
        return false;
    }

    std::cout << "Test passed: getHandleFromProcessID\n";
    return true;

 }


bool WindowTest::testGetWindowClassNameFromHWND() {

    //We need to create our own custom window for good test cases
  
    //Assuming there is an open window at point 400,400
    POINT pt = { 400, 400 };


    // Get the HWND from the point
    HWND hwndFromPoint = WindowAPI::getWindowFromPoint(pt);
    std::basic_string<TCHAR> className = WindowAPI::getWindowClassNameFromHWND(hwndFromPoint);

    if (!className.empty()) {

        std::cout << "Test passed: getWindowClassNameFromHWND\n";
        return true;
    }
    else {
        std::cout << "Test failed: getWindowClassNameFromHWND\n";
        return false;
    }
}



bool WindowTest::testGetExeFilePathFromHandle() {
    HANDLE handle = GetCurrentProcess();
    std::string exePath = WindowAPI::getExeFilePathFromHandle(handle);

    if (exePath.empty()) {

        std::cout << "Test falsed: getExeFilePathFromHandle\n";
        return false;
    }
    exePath = WindowAPI::getExeFilePathFromHandle(NULL);
    if (!exePath.empty()) {

        std::cout << "Test falsed: getExeFilePathFromHandle\n";
        return false;
    }
    std::cout << "Test passed: getExeFilePathFromHandle\n";
    return true;
}


bool WindowTest::testCloseHandle() {
    HANDLE handle = GetCurrentProcess();
    bool result = WindowAPI::closeHandle(handle);

    if (result) {
        std::cout << "Test passed: closeHandle\n";
        return true;
    }
    else {
        std::cout << "Test failed: closeHandle\n";
        return false;
    }
}