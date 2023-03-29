#pragma once

#include <attack.h>
#include <SFML/Graphics.hpp>
#include <enemy.h>
#include <tower.h>

class focuserAttack : public attack
{
private:
    /* data */
public:
    enemy* e;
    sf::Vector2f lastEnemyPosition;

    focuserAttack(tower* to, enemy* en){
        e = en;
        t = to;
        type = "focuserAttack";
        lastEnemyPosition.x = e->pos.x();
        lastEnemyPosition.y = e->pos.y();
        currenttime = 0;
        maxTime = 0.5f;
    }
};