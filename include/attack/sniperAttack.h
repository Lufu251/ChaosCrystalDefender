#pragma once

#include <attack.h>
#include <SFML/Graphics.hpp>
#include <enemy.h>
#include <tower.h>

class sniperAttack : public attack
{
private:
    /* data */
public:
    enemy* e;
    sf::Vector2f lastEnemyPosition;

    sniperAttack(tower* to, enemy* en){
        type = "sniperAttack";
        t = to;
        e = en;
        lastEnemyPosition.x = e->pos.x();
        lastEnemyPosition.y = e->pos.y();
        currenttime = 0;
        maxTime = 0.1f;
    }
};