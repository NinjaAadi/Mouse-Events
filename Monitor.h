#pragma once
#include <Windows.h>

/*
	Type: Monitor interface
	Description: Each monitor class should implement this, so that we can use decorator pattern.
*/
class Monitor {
public:
	
	//Common monitor function that each monitor class should have.
	virtual void monitor(const HWND hwnd) = 0;
};