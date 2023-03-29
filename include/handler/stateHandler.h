#pragma once

#include <gameState.h>

#include <iostream>

class stateHandler
{
private:
    /* data */
public:
    stateHandler(/* args */);
    ~stateHandler();

    void checkState(std::unique_ptr<gameState>& rState);
};