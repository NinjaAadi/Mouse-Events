#pragma once
#include "HookService.h"

class MouseCoordinates : public HookService<LRESULT(*)(int, WPARAM, LPARAM)> {
public:
    MouseCoordinates() {

    }
    static LRESULT mouseProc(int nCode, WPARAM wParam, LPARAM lParam); 
    HHOOK registerHook();
    void unregisterHook();

};

