#include <iostream>
#include "MouseCoordinatesTest.h"
#include "MouseCoordinates.h"
#include <thread>
#include <chrono>
#include "FileMonitor.h"
/*
    Type: MouseCoordinates test class implementation
    Descrption: 

*/
void MouseCoordinatesTest::runTests() {
    std::cout << "Running test cases for  Mouse Coordinates class...\n";
    if (testHook() &&
        testConstructor() &&
        testRegisterHook() &&
        testUnregisterHook()
    ) {

        std::cout << "Test case passed successfully\n";

    }
    else {

        std::cout << "Test case failed\n";
    }
}



bool MouseCoordinatesTest::testConstructor() {


    FileMonitor* fileMonitor = new FileMonitor();
    MouseCoordinates mouseCoordinates = MouseCoordinates(fileMonitor);

    if (mouseCoordinates.getCallBack() == NULL) {

        std::cout << "Test failed: MouseCoordinates callback constructor\n";
        return false;
    }
    std::cout << "Test passed: MouseCoordinates callback constructor\n";
    return true;
 }



bool MouseCoordinatesTest::testRegisterHook() {
    MouseCoordinates mouseCoordinates = MouseCoordinates();
    mouseCoordinates.setHook();


    if (mouseCoordinates.getHook() == NULL) {

        std::cout << "Test failed: Register Hook\n";
        mouseCoordinates.unHook();
        return false;
    }

    mouseCoordinates.unHook();

    std::cout << "Test passed: Register Hook\n";
    return true;

}



bool MouseCoordinatesTest::testUnregisterHook() {
    MouseCoordinates mouseCoordinates = MouseCoordinates();
    mouseCoordinates.setHook();
    mouseCoordinates.unHook();

    if (mouseCoordinates.getHook() != NULL) {

        std::cout << "Test failed: UnregisterHook Hook\n";
        
        return false;
    }

    

    std::cout << "Test passed: UnregisterHook Hook\n";
    return true;
}


bool MouseCoordinatesTest::testHook() {
        MouseCoordinates mouseCoordinates = MouseCoordinates();
        mouseCoordinates.setHook();

        POINT pt = { 10, 10 };
        PostMessage(NULL, WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));
        // Process the message queue
        MSG msg;
        std::cout << "Please move your continuously...";
        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Introduce a small delay


        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (mouseCoordinates.getIsCaptured()) break;
        }

        mouseCoordinates.unHook();

        if (!mouseCoordinates.getIsCaptured()) {

            std::cout << "Test failed: Mouse hook and monitor function\n";
            return false;
        }
        else std::cout << "Test passed: Mouse hook and monitor function\n";
        return true;
}