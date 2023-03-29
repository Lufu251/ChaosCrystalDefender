#pragma once

#include <entity.h>

#include <Eigen/Core>
#include <string>
#include <enemy.h>

class tower : public entity
{
protected:

public:
    float damage;
    float attackSpeed;
    float cooldown;
    float range;
    int currentCost = 0;
    int level = 0;
    float costAdd;
    float damageUpgrade;
    float rangeUpgrade;
    float speedUpgrade;
    enemy* attackedEnemy = nullptr;
    float rotation = 0;

    tower(){
        category = "tower";
    }
    virtual ~tower() = default;
};