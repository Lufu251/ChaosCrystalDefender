#include <buildMenu.h>

buildMenu::buildMenu(Eigen::Vector2i position)
{
    pos = position;
    buttons.push_back(menuButton(pos + Eigen::Vector2i(3,3), "zapper"));
    buttons.push_back(menuButton(pos + Eigen::Vector2i(46,3), "pulser"));
    buttons.push_back(menuButton(pos + Eigen::Vector2i(89,3), "freezer"));
    buttons.push_back(menuButton(pos + Eigen::Vector2i(3,86), "sniper"));
    buttons.push_back(menuButton(pos + Eigen::Vector2i(46,86), "focuser"));

    int rows = int(buttons.size() / 3 + 1);
    int cols = int(buttons.size());
    cols = std::min(cols, 3);
    size = Eigen::Vector2i(cols * 43 + 3, rows * 83 + 3);
}