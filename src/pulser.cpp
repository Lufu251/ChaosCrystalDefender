#include <pulser.h>

pulser::pulser(Eigen::Vector2f position, float damageValue, float attackSpeedValue, float rangeValue, int currentCostValue)
{
    pos = position;
    damage = damageValue;
    attackSpeed = attackSpeedValue;
    range = rangeValue;
    currentCost = currentCostValue;
    type = "pulser";
    size = 32;
    cooldown = attackSpeed;

    costAdd = 75;
    damageUpgrade = 2;
    rangeUpgrade = 0;
    speedUpgrade = 0;
}