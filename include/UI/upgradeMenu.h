#pragma once

#include <guiMenu.h>

class upgradeMenu : public guiMenu
{
private:
    /* data */
public:
    upgradeMenu() = default;
    upgradeMenu(Eigen::Vector2i position);
};