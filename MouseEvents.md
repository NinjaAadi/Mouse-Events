# Mouse Events
----
#### Description

A console based application that monitors the mouse cursor's co-ordinates in 2-dimentional plane, the executable file (.exe) and the class type (Ex: Button, Excel7 etc);

----
#### Tech stack
- C++
- Win32
- Visual studio

----
#### Depencencies
- 	Windows 2000 Professional (Min)
- 	Visual Studio
----
#### Steps
- Download latest Visual Studio community from https://visualstudio.microsoft.com/downloads/
- Open the setup.exe file
- Select Desktop development with C++ checkbox
- Click on the install
----
#### Configure the project
- Unzip the folder to desired location
- Open Visual Studio -> open the project
- Open Tools -> Command Line -> Developer Command prompt
- Run the below command to build the solution
```sh
msbuild MouseEvents.sln /t:Rebuild
```
You can remove /t: Rebuild if you don't want to rebuild
- Run the following command
```sh
"{PathToYourRepo}\x64\Debug\MouseEvents.exe"
```
The Mouse events monitoring will start

----
#### Steps to run Unit tests
- Open the command prompt in Visual Studio (Tools -> Command Line -> Developer Command prompt)
- Run the below command with this flag -test
```sh
"{PathToYourRepo}\x64\Debug\MouseEvents.exe" -test
```
- The tests will start running
- At certain point you need to move your mouse cursor fast, which is used to test the mouse hook.
----
#### Project description
- Naming convention : Lower Camel Case
- Folder structure
/Client
/WrapperWin32API : A wrapper to the set of APIs provided by Win32
|-----Header files
|-----Source files
/Services
|-----Header files
|-----Source files
/Test
- The Client folder contains the main.cpp file which is the entry point to the console application
- The WrapperWin32API is a bunch of wrapper classes around the win32 api provided to be used by the application. It directly interacts with the win32 api functions.
- The Service folder is a class which acts as a bridge between the client code and the win32 wrapper
- The test folder contains the unit test cases for each and every file.
----
#### Project flow
###### Note: The following codes are just gist of the project and not the whole program.Actual program is well commented and properly organized.

####   
####
##### Client
The client folder contains *main.cpp*  file which is the entry point of the application.
##### Service
The Service folder has MouseCoordinates service class which is the following
```cpp
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
```
We can use *startMonitor()* function to start the monitoring of the application.
If you go to *MouseCoordinatesService()* implementation, we have the below,
```cpp
MouseCoordinatesService::MouseCoordinatesService() {
	setHighDPIAwareness();	
	win32MouseCoordinates = MouseCoordinates(new FileMonitor(new ItemMonitor()));
	win32MouseCoordinates.setHook();

}
```

The File Monitor and Item Monitor are independent monitor classes, that helps to monitor file names and class names of the window,


If you notice this line 
```cpp
MouseCoordinates(new FileMonitor(new ItemMonitor()));
```
This uses iterator pattern or callback mechanism to decouple the monitorning classes with hook class.

If suppose we want only File Monitor service, we can just provide
```cpp
MouseCoordinates(new FileMonitor())
```

In future if we introduce any new Hooks or any new Monitor service, we can do it very easily, without class for each required functionality.

##### WrapperWin32API

If you see *MouseCoordinates* class
```cpp
/*
    Type: Mouse Hook Class
    Description: Mouse hook class which extends HookService 
    *IMPORTANT: The callback class here is static, so if you register a callback function it will be same for all the instance
    * This is a tradeoff for scalable code
*/
class MouseCoordinates : public HookService {
public:

    MouseCoordinates();
    MouseCoordinates(Monitor* _callBack);
    static void monitorPoints(POINT point);
    ~MouseCoordinates();
    bool getIsCaptured();
    Monitor* getCallBack();

protected:
    static LRESULT mouseProc(int nCode, WPARAM wParam, LPARAM lParam); //Mouse proceduce definition
    HHOOK registerHook() override;
    void unregisterHook() override;

    static Monitor* callBack; //Callback class such as FileMonitor or ItemMonitor

private:
    static bool isCaptured; //For testing purpose
};
```
It implements *HookService*, which needs to be implemented by each and every Hooks introduced.

- Hooks: In the Win32 API, hooks are mechanisms that allow an application to intercept and respond to events or messages before they reach their intended destination. Hooks provide a way to monitor or modify the behavior of input events (like keyboard and mouse events), system messages, and other processes.
- We need to have a static function which gets called when a mouse event is emitted
- In this case it is *static LRESULT mouseProc(...)*
- Since the mouseProc function is static, we need to have the callBacks static, which means only one instance of hooks could run at a time, which has callbacks. If we change the callback for one instance, it will change for each and every instance. This is a tradeoff for scalability.

This is the base class for the decorator pattern. In future if we introduce any other hooks, it. We can read more about Decorator pattern from here, https://en.wikipedia.org/wiki/Decorator_pattern

##### Monitor
Now, go to *Monitor* class
```cpp
/*
	Type: Monitor interface
	Description: Each monitor class should implement this, so that we can use decorator pattern.
*/
class Monitor {
public:
	
	//Common monitor function that each monitor class should have.
	virtual void monitor(const HWND hwnd) = 0;
};
```



Currently there are two types of callback,
- FileMonitor
- ItemMonitor
Here is one the Monitor class

```cpp
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
```
Each callback has the monitor function which needs to call the next callback using
```cpp
callBack->monitor(hwnd)
```
after the execution of the current callback.


Each monitor needs to implement the monitor function, so that it could be used as a callback mechanism.
The hooks provide general information such as Points or KeyStrokes, we need to get the handle to the window to get information like FileName and ItemName, so the decoupling of the hooks, with the monitor items are necessary. The monitor items uses HWND(Data type) which is Handle to the window to fetch information. So we can pass that to the callbacks using
callback->monitor(hwnd)



##### Function -> Window

If you see the *WindowAPI* class, it has a set of wrapper functions for WIN32 Api.
```Cpp
class WindowAPI {
public:
	static HWND getWindowFromPoint(POINT point); //Get handle to the window(HWND) from point class

	static DWORD getProcessIDFromHWND(HWND hwnd); //Get process id from handle

	static HWND getChildWindowFromPoint(HWND parntHWND, POINT pt); //Get child HWND from parent handle and point

	static HANDLE getHandleFromProcessID(DWORD access,BOOL inheritHandle,DWORD processID); //Get handle from handle to the window

	static std::basic_string<TCHAR> getWindowClassNameFromHWND(HWND hwnd); //Get class name of inner item from Handle

	static std::string getExeFilePathFromHandle(HANDLE handle); //Get file path from handle

	static bool closeHandle(HANDLE handle); //Close the handle
};
```

##### Test
This folder contains the unit test cases for each and every member functions
It has *testMain()* function which runs all the test
The test could by dynamically linked, with the mouse Events project, but for the sake of simplicity, we have done static linking. If we want, we can also make a seperate *dll* for the test folder.
####
####
----
For referernce, we can use https://learn.microsoft.com/en-us/windows/win32/api/

