#include <focuser.h>

focuser::focuser(Eigen::Vector2f position, float damageValue, float attackSpeedValue, float rangeValue, int currentCostValue)
{
    pos = position;
    damage = damageValue;
    attackSpeed = attackSpeedValue;
    range = rangeValue;
    currentCost = currentCostValue;
    type = "focuser";
    size = 32;
    cooldown = attackSpeed;

    costAdd = 100;
    damageUpgrade = 0.25f;
    rangeUpgrade = 0;
    speedUpgrade = 0.2f;
}