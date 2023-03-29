#pragma once

#include <inputHandler.h>
#include <gameState.h>
#include <dataHandler.h>
#include <tileGrid.h>
#include <tileRenderer.h>
#include <assets.h>
#include <entityRenderer.h>
#include <enemyHandler.h>
#include <towerHandler.h>
#include <dachView.h>
#include <gameHandler.h>
#include <guiRenderer.h>
#include <attackHandler.h>
#include <attackRenderer.h>
#include <button.h>

#include <SFML/Graphics.hpp>

class playState : public gameState
{
private:
    buttonHandler buttonH;
    dataHandler dataH;
    tileRenderer tileR;
    assets gameAssets;
    entityRenderer entityR;
    enemyHandler enemyH;
    towerHandler towerH;
    gameHandler gameH;
    guiRenderer guiR;
    attackRenderer attackR;
    attackHandler attackH;


    Eigen::Vector2f positionOld;

    sf::Clock clock;
    sf::Music music;

    dachView gameView;
    dachView guiView;

public:
    playState(/* args */);
    void update(sf::RenderWindow &rWindow, inputHandler &rInputH);
    void draw(sf::RenderWindow &rWindow, inputHandler &rInputH);
    void init();
    void moveView(inputHandler &rInputH, dachView& rDachView);
    void zoomView(inputHandler &rInputH, dachView &rDachView);
};