#include <sniper.h>

sniper::sniper(Eigen::Vector2f position, float damageValue, float attackSpeedValue, float rangeValue, int currentCostValue)
{
    pos = position;
    damage = damageValue;
    attackSpeed = attackSpeedValue;
    range = rangeValue;
    currentCost = currentCostValue;
    type = "sniper";
    size = 32;
    cooldown = attackSpeed;

    costAdd = 100;
    damageUpgrade = 16;
    rangeUpgrade = 8;
    speedUpgrade = 0;
}