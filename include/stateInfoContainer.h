#pragma once

#include <iostream>

class stateInfoContainer
{
    public:
    bool close = false;
    int nextState = 0;

    void setNextState(int index){
        close = true;
        nextState = index;
    }
};