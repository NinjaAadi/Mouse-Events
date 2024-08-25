#pragma once
#include <iostream>
#include "WindowTitleMonitor.h"
#include "Window.h";


void WindowTitleMonitor::monitor(const HWND hwnd) {
	if (hwnd) {
		std::string windowTitle = WindowAPI::getWindowTitle(hwnd);
		if (!windowTitle.empty()) {
			std::cout << " : " << windowTitle << " ";
		}
		else {
			std::cout << "UNDEFINED ";
		}
	}

	//Call the callback
	if (callBack) {
		callBack->monitor(hwnd);
	}
	else {
		std::cout << std::endl;
	}
}


//Constructor with callback
WindowTitleMonitor::WindowTitleMonitor(Monitor* _callBack) {
	callBack = _callBack;
}


WindowTitleMonitor::WindowTitleMonitor() {

}

Monitor* WindowTitleMonitor::getCallBack() {
	return callBack;
}

