#pragma once

#include <tower.h>

class freezer : public tower
{

public:
    freezer(Eigen::Vector2f position, float damageValue, float attackSpeedValue, float rangeValue, int currentCostValue);
};