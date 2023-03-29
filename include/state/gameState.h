#pragma once

#include <inputHandler.h>
#include <stateInfoContainer.h>
#include <dataHandler.h>

#include <SFML/Graphics.hpp>

class gameState
{
private:
    /* data */
public:
    stateInfoContainer stateInfo;

    virtual ~gameState() = default;

    virtual void update(sf::RenderWindow &rWindow, inputHandler &rInputH) = 0;
    virtual void draw(sf::RenderWindow &rWindow, inputHandler &rInputH) = 0;
    virtual void init() = 0;
};