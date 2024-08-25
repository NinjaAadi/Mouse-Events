#pragma once
#include "HookService.h"
#include <functional>
#include "Monitor.h"


/*
    Type: Mouse Hook Class
    Description: Mouse hook class which extends HookService 
    *IMPORTANT: The callback class here is static, so if you register a callback function it will be same for all the instance
    * This is a tradeoff for scalable code
*/
class MouseCoordinates : public HookService {
public:


    MouseCoordinates();
    MouseCoordinates(Monitor* _callBack);
    static void monitorPoints(POINT point);
    ~MouseCoordinates();
    bool getIsCaptured();
    Monitor* getCallBack();

protected:
    static LRESULT mouseProc(int nCode, WPARAM wParam, LPARAM lParam); //Mouse proceduce definition
    HHOOK registerHook() override;
    void unregisterHook() override;

    static Monitor* callBack; //Callback class such as FileMonitor or ItemMonitor

private:
    static bool isCaptured; //For testing purpose
};




