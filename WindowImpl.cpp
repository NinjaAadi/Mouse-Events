#pragma once

#include "Window.h"
#include <Psapi.h>
#include <iostream>
#include <vector>
#include <windows.h>

/*
	Type: WindowAPI implementation
	Description: Functions which uses direct Win32 API provided by Microsoft
*/



//Get handle to a window(HWND) from a point
HWND WindowAPI::getWindowFromPoint(POINT point) {
	
	return WindowFromPoint(point);
}


//Get handle to the window from point and parent window
HWND WindowAPI :: getChildWindowFromPoint(HWND parentHWND,POINT pt) {

	return RealChildWindowFromPoint(parentHWND, pt);
}


//Get processId for the handle 
DWORD WindowAPI::getProcessIDFromHWND(HWND hwnd) {

	DWORD processID = NULL;
	GetWindowThreadProcessId(hwnd, &processID);
	return processID;
}

//Get Handle pointer from processID
HANDLE WindowAPI::getHandleFromProcessID(DWORD access,BOOL inheritHandle, DWORD processID) {

		return OpenProcess(access,
			inheritHandle, processID);
}


//Get window class name from Handle to the window
std::basic_string<TCHAR> WindowAPI::getWindowClassNameFromHWND(HWND hwnd) {

	TCHAR className[MAX_CLASS_NAME];
	if (RealGetWindowClass(hwnd, className, MAX_CLASS_NAME)) {

		return std::basic_string<TCHAR>(className);
	}
	return std::basic_string<TCHAR>();
}



//Get File path from the handle
std::string WindowAPI::getExeFilePathFromHandle(HANDLE handle){
		char exePath[MAX_PATH];
		if (GetModuleFileNameExA(handle, NULL, exePath, MAX_PATH)) {
			return std::string(exePath);
		}
		return std::string(); 
}



//Get the title of the window from the handle to the window
/*int GetWindowTextA(
	[in]  HWND  hWnd,
	[out] LPSTR lpString,
	[in]  int   nMaxCount
);*/


std::string  WindowAPI::getWindowTitle(const HWND hwnd) {
	char title[MAX_PATH];

	if (GetWindowTextA(hwnd, title, MAX_PATH)) {
		return std::string(title);
	}
	return std::string();
}

//Function to close the handle
bool WindowAPI::closeHandle(HANDLE handle) {
	return CloseHandle(handle);
}

