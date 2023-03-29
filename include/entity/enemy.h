#pragma once

#include <entity.h>
#include <enemy.h>

#include <Eigen/Core>
#include <string>

class enemy : public entity
{
protected:

public:
    float currentHealth;
    float maxHealth;
    float speed;
    float progression;
    
    float targetTime = 0;
    float targetStrength = 0;
    bool targeted = false;

    float freezeTime = 0;
    float freezeStrength = 0;
    bool freezed = false;
    bool isDead = false;

    enemy(){
        category = "enemy";
    }
    virtual ~enemy() = default;
};