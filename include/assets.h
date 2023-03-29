#pragma once
#include <tileGrid.h>
#include <tower.h>
#include <entity.h>
#include <enemy.h>
#include <attack.h>
#include <memory>

#include <vector>

struct assets
{
    int money = 800;
    int baseHealth = 10;
    int baseHealthMax = 10;
    int nextWave = 20;
    int waveCount = 1;
    tileGrid grid = tileGrid(17, 17);
    std::vector<entity*> entities;
    std::vector<std::unique_ptr<enemy>> enemys;
    std::vector<std::unique_ptr<tower>> towers;
    std::vector<std::unique_ptr<attack>> attacks;
};