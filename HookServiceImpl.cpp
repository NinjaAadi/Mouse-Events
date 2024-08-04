#pragma once
#include "HookService.h"

/*
    Type: HookService implementation
    Description: Implementation of standard function of HookService
*/
void HookService::unHook() {

    if (hhook) {

        unregisterHook();
        hhook = NULL;
    }
}

void HookService::setHook() {

    if (!hhook) {

        //Register hook
        this->hhook = registerHook();
        if (!hhook) {

            std::cout << "Hook registration failed...\n";
        }
    }
}

HHOOK HookService::getHook() {
    return hhook;
}