#pragma once

#include <tower.h>
#include <enemy.h>

class focuser : public tower
{
public:
    float addedDamage = 0;
    enemy* lastEnemy = nullptr;
    focuser(Eigen::Vector2f position, float damageValue, float attackSpeedValue, float rangeValue, int currentCostValue);
};