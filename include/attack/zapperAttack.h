#pragma once

#include <attack.h>
#include <SFML/Graphics.hpp>
#include <enemy.h>
#include <tower.h>

class zapperAttack : public attack
{
private:
    /* data */
public:
    enemy* e;
    sf::Vector2f lastEnemyPosition;

    zapperAttack(tower* to, enemy* en){
        type = "zapperAttack";
        t = to;
        e = en;
        lastEnemyPosition.x = e->pos.x();
        lastEnemyPosition.y = e->pos.y();
        currenttime = 0;
        maxTime = 0.2f;
    }
};