#pragma once

#include <tileGrid.h>
#include <dataHandler.h>
#include <SFML/Graphics.hpp>

class tileRenderer
{
private:
    
public:
    tileRenderer(/* args */);
    ~tileRenderer();

    void setTileSize(size_t size);
    void renderTiles(sf::RenderWindow& rWindow, dataHandler& rDataH, tileGrid& tg);
};