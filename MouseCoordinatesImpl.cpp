#pragma once
#include "MouseCoordinatesService.h"

/*
	Type: Mouse Coordinates Service Implementation
	Description: Implementation functions for MouseCoordinatesService
*/
void MouseCoordinatesService::startMonitor(){

	
	 //Get continuous messege from mouse 
	 MSG msg;
	 while (GetMessage(&msg, NULL, 0, 0)) {

		 TranslateMessage(&msg);
		 DispatchMessage(&msg);
	 }
}

MouseCoordinatesService::~MouseCoordinatesService(){

	win32MouseCoordinates.unHook();
}

/*
	If you want to monitor on certain order, you can change the order, or remove the callback classes
	Ex: I want only ItemMonitor(), then
	win32MouseCoordinates = MouseCoordinates(new ItemMonitor()));
*/
MouseCoordinatesService::MouseCoordinatesService() {
	setHighDPIAwareness();	
	win32MouseCoordinates = MouseCoordinates(new FileMonitor(new ItemMonitor(new WindowTitleMonitor())));
	win32MouseCoordinates.setHook();

}

void MouseCoordinatesService::setHighDPIAwareness() {
	BOOL dpi_result = SetProcessDPIAware();
}