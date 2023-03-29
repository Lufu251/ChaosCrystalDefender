#pragma once
#include <gameState.h>
#include <inputHandler.h>
#include <dataHandler.h>
#include <button.h>

#include <SFML/Graphics.hpp>

class menuState : public gameState
{
private:
    buttonHandler buttonH;
    dataHandler dataH;
    sf::Music music;
    
public:
    menuState();
    void update(sf::RenderWindow &rWindow, inputHandler &rInputH);
    void draw(sf::RenderWindow &rWindow, inputHandler &rInputH);
    void init();
};