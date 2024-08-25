#pragma once
#include "Monitor.h"

class WindowTitleMonitor : public Monitor {
public:
	void monitor(const HWND hwnd);
	WindowTitleMonitor(Monitor* _callBack);
	WindowTitleMonitor();
	Monitor* getCallBack();
private:
	Monitor* callBack = nullptr;
};