#pragma once

#include <guiMenu.h>

class buildMenu : public guiMenu
{
private:
    /* data */
public:
    buildMenu() = default;
    buildMenu(Eigen::Vector2i position);
};