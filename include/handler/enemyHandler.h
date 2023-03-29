#pragma once

#include <enemy.h>
#include <tileGrid.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <assets.h>

#include <iostream>
#include <vector>

class enemyHandler
{
private:
    /* data */
public:

    void moveEnemys(std::vector<std::unique_ptr<enemy>>& rEnemys, tileGrid& grid, sf::Time& elapsed);
    void isAtBase(assets& rGameAsset);
    void removeDead(assets &rGameAsset);
    void updateStatus(assets& rGameAsset, sf::Time elapsed);
};