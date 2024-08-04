#pragma once
#include "MouseCoordinates.h"
#include "FileMonitor.h"
#include "ItemMonitor.h"




/*
	Type: Service Layer class
	Description: Mouse Coordinate service class to interact b/w WIN32 Layer and Client Layer
*/
class MouseCoordinatesService {
public:

	MouseCoordinates win32MouseCoordinates; //Win32 API Layer class 

	MouseCoordinatesService();
	~MouseCoordinatesService();


	//Function to start the mouse co-ordinate monitoring
	void startMonitor();

	//Function to set awareness for high DPI screens, so that the program works fine with each DPI screen
	//*IMPORTANT: This should be called in the constructor
	void setHighDPIAwareness();

};