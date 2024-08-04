#pragma once
#include "MouseCoordinatesService.h"
#include "TestMain.h"

// Uncomment the following line to build in test environment
//#define TEST_ENVIRONMENT




// Entry point 
int main(int argc, char* argv[]) {


#ifdef _WIN32
    // Check if environment is set for testing
#ifdef TEST_ENVIRONMENT



    // Run tests if in the test environment
    testMain();
#else
    bool runTests = false;
    for (int i = 0; i < argc; ++i) {
        if (std::string(argv[i]) == "-test") {
            runTests = true;
            break;
        }
    }
    if (runTests) {
        
        //Run the test main function
        testMain();
    }
    else {
        // Client code for production environment
        MouseCoordinatesService mouseCoordinatesService;
        mouseCoordinatesService.startMonitor();

    }
#endif
#else
    // Notify that the OS is not Windows
    std::cerr << "This application is designed to run on Windows." << std::endl;
#endif

    return 0;
}
