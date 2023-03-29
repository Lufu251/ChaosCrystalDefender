#pragma once

#include <string>
#include <random>


struct tile
{
    bool blocking = false;
    std::string type = "tile1";
    int cost = 10000;
};
