#include <freezer.h>

freezer::freezer(Eigen::Vector2f position, float damageValue, float attackSpeedValue, float rangeValue, int currentCostValue)
{
    pos = position;
    damage = damageValue;
    attackSpeed = attackSpeedValue;
    range = rangeValue;
    currentCost = currentCostValue;
    type = "freezer";
    size = 32;
    cooldown = attackSpeed;

    costAdd = 75;
    damageUpgrade = 0.5f;
    rangeUpgrade = 2;
    speedUpgrade = 0.4f;
}