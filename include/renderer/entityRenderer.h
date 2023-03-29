#pragma once

#include <SFML/Graphics.hpp>
#include <dataHandler.h>
#include <entity.h>
#include <enemy.h>
#include <tower.h>

class entityRenderer
{
private:
    /* data */
public:
    entityRenderer(/* args */);
    ~entityRenderer();

    void renderEntities(sf::RenderWindow& rWindow, dataHandler& rDataH, std::vector<entity*>& rEntities);
};