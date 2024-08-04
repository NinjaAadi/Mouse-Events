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


//Print point and call the next callback
void MouseCoordinates::monitorPoints(POINT point) {
    isCaptured = true;
    std::cout << "{" << point.x << "," << point.y << "}";


    if (callBack) {

        callBack->monitor(WindowAPI::getWindowFromPoint(point));
    }
    
    else std::cout << std::endl;
}


//This is a static function that is called when mouse emits messeges
LRESULT MouseCoordinates::mouseProc(int nCode, WPARAM wParam, LPARAM lParam){

    if (nCode >= HC_ACTION) {

        MSLLHOOKSTRUCT* mouseStruct = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam); //lParam is a pointer to the MSLLHOOKSTRUCT class which contains info about mouse event
        POINT pt = mouseStruct->pt;
        monitorPoints(pt);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
    
}




