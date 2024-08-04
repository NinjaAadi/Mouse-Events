#pragma once
#include "Monitor.h"
#include <string>

/*
	Type: File monitor class
	Description: Handle files from windowHandle
*/
class FileMonitor : public Monitor {
public:


	void monitor(const HWND hwnd); //Function to get filename from handle to the window
	FileMonitor();
	FileMonitor(Monitor* _callBack);
	std::string getFile(const HWND hwnd);
	std::string getFileName(std::string& path); 
	Monitor* getCallBack();

private:
	Monitor* callBack = nullptr; //Next callback class
	
};