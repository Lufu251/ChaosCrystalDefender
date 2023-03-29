#pragma once

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <assets.h>
#include <dataHandler.h>
#include <cmath>
#include <zapperAttack.h>
#include <pulserAttack.h>
#include <freezerAttack.h>
#include <focuserAttack.h>
#include <sniperAttack.h>
#include <string>

class attackRenderer
{
public:

    void renderAttacks(sf::RenderWindow &rWindow, assets &rGameAsset, dataHandler& rDataH);
    sf::RectangleShape drawLine(sf::Vector2f startPoint, sf::Vector2f endPoint, float thickness, sf::Color color);
};