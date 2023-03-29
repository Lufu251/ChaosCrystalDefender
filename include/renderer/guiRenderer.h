#pragma once

#include <SFML/Graphics.hpp>
#include <dataHandler.h>
#include <assets.h>
#include <gameHandler.h>
#include <algorithm>
#include <sstream>

class guiRenderer
{
private:
    /* data */
public:
    void renderBaseHealth(sf::RenderWindow &rWindow, assets &rGameAsset, dataHandler &rDataH);
    void renderMoney(sf::RenderWindow &rWindow, assets &rGameAsset, dataHandler &rDataH);
    void renderWaveDisplay(sf::RenderWindow &rWindow, assets &rGameAsset, dataHandler &rDataH);
    void renderTowerRange(sf::RenderWindow &rWindow, assets &rGameAsset, gameHandler &rGameH);
    void renderSelectedTower(sf::RenderWindow &rWindow, assets &rGameAsset, gameHandler &rGameH, dataHandler &rDataH);
    void renderMessage(sf::RenderWindow &rWindow, assets &rGameAsset, gameHandler &rGameH, dataHandler &rDataH);
    void renderGameMenu(sf::RenderWindow &rWindow, assets &rGameAsset, gameHandler &rGameH, dataHandler &rDataH);
};
