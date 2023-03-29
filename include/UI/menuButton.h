#pragma once

#include <Eigen/Core>

struct menuButton
{
    std::string action;
    Eigen::Vector2i pos;
    int sizeX = 40;
    int sizeY = 80;

    menuButton(Eigen::Vector2i position, std::string actionType) : pos(position), action(actionType){

    }
};
