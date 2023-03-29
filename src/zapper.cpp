#include <zapper.h>

zapper::zapper(Eigen::Vector2f position, float damageValue, float attackSpeedValue, float rangeValue, int currentCostValue)
{
    pos = position;
    damage = damageValue;
    attackSpeed = attackSpeedValue;
    range = rangeValue;
    currentCost = currentCostValue;
    type = "zapper";
    size = 32;
    cooldown = attackSpeed;

    costAdd = 25;
    damageUpgrade = 2;
    rangeUpgrade = 0;
    speedUpgrade = 0.1f;
}