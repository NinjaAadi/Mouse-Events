#pragma once
#include<Windows.h>
#include<string>


/*
	Type : Window API interface
	Description: Set of functions provided by the Win32 API (Customized);]
*/
class WindowAPI {
public:
	static HWND getWindowFromPoint(POINT point); //Get handle to the window(HWND) from point class

	static DWORD getProcessIDFromHWND(HWND hwnd); //Get process id from handle

	static HWND getChildWindowFromPoint(HWND parntHWND, POINT pt); //Get child HWND from parent handle and point

	static HANDLE getHandleFromProcessID(DWORD access,BOOL inheritHandle,DWORD processID); //Get handle from handle to the window

	static std::basic_string<TCHAR> getWindowClassNameFromHWND(HWND hwnd); //Get class name of inner item from Handle

	static std::string getExeFilePathFromHandle(HANDLE handle); //Get file path from handle

	static bool closeHandle(HANDLE handle); //Close the handle

	static std::string getWindowTitle(const HWND hwnd);
};


 