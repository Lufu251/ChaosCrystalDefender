#pragma once

#include <string>
#include <enemy.h>
#include <tower.h>

class attack
{
public:
    tower* t;

    std::string type;
    float currenttime;
    float maxTime;
    bool damage = true;
    bool isDead = false;
    bool enemyIsDead = false;

    virtual ~attack() = default;
};