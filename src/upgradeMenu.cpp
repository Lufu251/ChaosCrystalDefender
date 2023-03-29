#include <upgradeMenu.h>

upgradeMenu::upgradeMenu(Eigen::Vector2i position)
{
    pos = position;
    buttons.push_back(menuButton(pos + Eigen::Vector2i(3,3), "upgrade"));
    buttons.push_back(menuButton(pos + Eigen::Vector2i(46,3), "sell"));

    int rows = int(buttons.size() / 3) + 1;
    int cols = int(buttons.size());
    int discard = std::min(cols, 3);
    size = Eigen::Vector2i(cols * 43 + 3, rows * 83 + 3);
}
