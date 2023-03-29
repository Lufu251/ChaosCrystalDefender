#pragma once

#include <tower.h>

class sniper : public tower
{
public:
    sniper(Eigen::Vector2f position, float damageValue, float attackSpeedValue, float rangeValue, int currentCostValue);
};