#pragma once

#include <tower.h>

class zapper : public tower
{
public:
    zapper(Eigen::Vector2f position, float damageValue, float attackSpeedValue, float rangeValue, int currentCostValue);  
};
