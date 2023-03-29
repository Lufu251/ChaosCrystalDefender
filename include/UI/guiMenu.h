#pragma once

#include <Eigen/Core>
#include <menuButton.h>

class guiMenu
{
private:
    /* data */
public:
    Eigen::Vector2i pos;
    Eigen::Vector2i size;
    std::vector<menuButton> buttons;

    virtual ~guiMenu() = default;
};