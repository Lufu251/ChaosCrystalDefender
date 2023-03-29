#pragma once

#include <assets.h>
#include <SFML/System.hpp>
#include <focuser.h>
#include <zapperAttack.h>
#include <pulserAttack.h>
#include <freezerAttack.h>
#include <sniperAttack.h>
#include <focuserAttack.h>

class attackHandler
{
public:

    void updateTime(assets &rGameAsset, sf::Time elapsed);
    void checkTime(assets &rGameAsset);
    void checkDeadEnemyAndSetLastEnemyPosition(assets &rGameAsset);
    void removeDeadAttacks(assets &rGameAsset);
    void doDamage(assets &rGameAsset);
};