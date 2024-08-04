#pragma once
#include "ItemMonitor.h"
#include <Windows.h>
#include "Window.h"
#include <iostream>

/*
	Type: Item monitor class implementation
	Descriptions: Implementation functions for Item Monitor
*/


//Function to monitor item name
void ItemMonitor::monitor(const HWND hwnd) {


	std::basic_string<TCHAR> className = WindowAPI::getWindowClassNameFromHWND(hwnd);
	if (!className.empty()) {

		std::wcout << " : " << className << " ";
	}
	else std::cout << " :  UNDEFINED";



	//Do not remove this callback chain
	if (callBack) {

		callBack->monitor(hwnd);
	}
	else std::cout << std::endl<<std::endl;
}

ItemMonitor::ItemMonitor() {

}
ItemMonitor::ItemMonitor(Monitor* _callBack) {

	this->callBack = _callBack;
}

Monitor* ItemMonitor::getCallBack()
{
	return callBack;
}
