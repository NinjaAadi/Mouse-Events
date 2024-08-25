#pragma once
#include "MouseCoordinates.h"
#include <Psapi.h>
#include "Window.h"


/*
    Type: Mouse Coordinates class implenentation
    Description: Implementation to all the functions of Mouse Coordinates class
*/
Monitor* MouseCoordinates::callBack = nullptr;
bool MouseCoordinates::isCaptured = false;


    




MouseCoordinates::MouseCoordinates() {}
MouseCoordinates::~MouseCoordinates() {
    isCaptured = false;
}




MouseCoordinates::MouseCoordinates(Monitor* _callBack) {

    this->callBack = _callBack;
}


//Register hook to the system

/*
    The first parameter is the type of hook
    The second parameter is the function pointer to the procedure
    The third paramter is the handle to the dll, if the mouesProc is in other dll
    The fourth parameter is the thread Id for which the hook is registered, if provided 0, then it is for all the
    running threads.
*/
HHOOK MouseCoordinates::registerHook() {
    
    return SetWindowsHookEx(WH_MOUSE_LL, mouseProc, NULL, 0);
}








Monitor* MouseCoordinates::getCallBack() {
    return callBack;
}






void MouseCoordinates:: unregisterHook() {
    UnhookWindowsHookEx(hhook);
}






bool MouseCoordinates::getIsCaptured() {
    return isCaptured;
}










/*
    Print point and call the next callback
    callBack is a type of monitor * which stores the next monitor function that has defined
*/
void MouseCoordinates::monitorPoints(POINT point) {
    isCaptured = true;
    std::cout << "{" << point.x << "," << point.y << "}";


    if (callBack) {

        callBack->monitor(WindowAPI::getWindowFromPoint(point));
    }
    
    else std::cout << std::endl;
}








/*
    This is a static function that is called when mouse emits messeges
    LRESULT
        #ifdef _WIN64
        typedef __int64 LONG_PTR;
        #else
        typedef long LONG_PTR;
        #endif
    WPARAM
        WM_MOUSEMOVE: Indicates that the mouse has moved.
        WM_LBUTTONDOWN: Indicates that the left mouse button was pressed.
        WM_LBUTTONUP: Indicates that the left mouse button was released.
        WM_RBUTTONDOWN: Indicates that the right mouse button was pressed.
        WM_RBUTTONUP: Indicates that the right mouse button was released.
        WM_MBUTTONDOWN: Indicates that the middle mouse button was pressed.
        WM_MBUTTONUP: Indicates that the middle mouse button was released.
        WM_MOUSEWHEEL: Indicates that the mouse wheel was rotated.
        WM_XBUTTONDOWN: Indicates that one of the additional mouse buttons (X1 or X2) was pressed.
        WM_XBUTTONUP: Indicates that one of the additional mouse buttons (X1 or X2) was released.

    RPARAM
    Pointer to the below structure
       typedef struct tagMSLLHOOKSTRUCT {
            POINT   pt;
            DWORD   mouseData;
            DWORD   flags;
            DWORD   time;
            ULONG_PTR dwExtraInfo;
        } MSLLHOOKSTRUCT, FAR *LPMSLLHOOKSTRUCT, *PMSLLHOOKSTRUCT;
*/



LRESULT MouseCoordinates::mouseProc(int nCode, WPARAM wParam, LPARAM lParam){

    //If we return 0, it indicates that the messege has been processed.
    if (nCode >= HC_ACTION) {  //If nCode is neg, then we don't need to process this hook

        MSLLHOOKSTRUCT* mouseStruct = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam); //lParam is a pointer to the MSLLHOOKSTRUCT class which contains info about mouse event
        POINT pt = mouseStruct->pt;
        monitorPoints(pt);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
    
}
