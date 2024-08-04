#pragma once
#include "FileMonitor.h"
#include <Windows.h>
#include "Window.h"
#include <iostream>

/*
	Type: File Monitor class implementation
	Descriptions: Implementation functions for File Monitor
*/


//Function to monitor file name
void FileMonitor::monitor(const HWND hwnd) {


	DWORD processID = WindowAPI::getProcessIDFromHWND(hwnd);
	HANDLE handle = WindowAPI::getHandleFromProcessID(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);


		if (handle) {

			std::string fileName = WindowAPI::getExeFilePathFromHandle(handle);
			if (!fileName.empty()) {

				std::cout << " : " << getFileName(fileName) << " ";
			}
			else std::cout << ": NO EXECUTABLE FILE ";
			WindowAPI::closeHandle(handle);
		}
		else {
			std::cout << ": NO EXECUTABLE FILE ";
		}
		

	//Do not remove this callback chain
	if (callBack) {

		callBack->monitor(hwnd);
	}
	else std::cout << std::endl;
}


std::string FileMonitor::getFile(const HWND hwnd) {
	DWORD processID = WindowAPI::getProcessIDFromHWND(hwnd);
	HANDLE handle = WindowAPI::getHandleFromProcessID(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);


	if (handle) {

		std::string fileName = WindowAPI::getExeFilePathFromHandle(handle);
		if (!fileName.empty()) {

			return getFileName(fileName);
		}
		else return "";
		WindowAPI::closeHandle(handle);
	}
	else {
		return "";
	}
}
//Function to get the application name(.exe) from file path
std::string FileMonitor:: getFileName(std::string& path) {

	size_t pos = path.find_last_of("\\/");
	return path.substr(pos + 1);
}
Monitor* FileMonitor::getCallBack()
{
	return callBack;
}
FileMonitor::FileMonitor() {

}
FileMonitor::FileMonitor(Monitor* _callBack) {

	this->callBack = _callBack;
}
