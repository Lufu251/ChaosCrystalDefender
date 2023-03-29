#pragma once

#define _USE_MATH_DEFINES
#include <vector>
#include <string>
#include <cmath>

#include <zapperAttack.h>
#include <pulserAttack.h>
#include <freezerAttack.h>
#include <sniperAttack.h>
#include <focuserAttack.h>
#include <tower.h>
#include <assets.h>
#include <Eigen/Core>
#include <SFML/System.hpp>

class towerHandler
{
private:
    /* data */
public:
    void updateCooldown(std::vector<std::unique_ptr<tower>>& rTowers, sf::Time &rDelta);
    void checkAttackedEnemyIsDead(assets &rGameAsset);
    std::vector<int> getEnemysToAttackSorted(tower* currentTower, assets &rGameAsset);
    void attack(assets &rGameAsset);
    void calculateRotation(assets &rGameAsset);
};