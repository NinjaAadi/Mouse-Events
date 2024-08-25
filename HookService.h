#pragma once
#include<Windows.h>
#include<iostream>



/*
	Type: Hook interface
	Description: Each hook registered need to implement HookService
*/
class HookService {
	public:

		virtual void unHook();  //Unset the hook
		virtual void setHook(); //Set the hook into the system
		virtual HHOOK getHook(); //Function to get the hook

	protected:

		HHOOK hhook = NULL;
		virtual HHOOK registerHook() = 0;
		virtual void unregisterHook() = 0;
};

/*
	HHOOK -> Handle to the hook
*/
