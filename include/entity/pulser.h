#pragma once

#include <tower.h>

class pulser : public tower
{
private:
    /* data */
public:
    pulser(Eigen::Vector2f position, float damageValue, float attackSpeedValue, float rangeValue, int currentCostValue);
};
