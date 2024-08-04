#pragma once
#include "Monitor.h"

/*
	Type: Item Monitor class 
	Description: Monitors the inner item type of the window 
*/

class ItemMonitor : public Monitor {
public:
	void monitor(const HWND hwnd); //Function that monitors the inner class item from the window handle
	ItemMonitor();
	ItemMonitor(Monitor* _callBack);
	Monitor* getCallBack();

private:
	Monitor* callBack = nullptr; //Next callback class
};

