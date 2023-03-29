#pragma once

#include <string>
#include <assets.h>
#include <enemy.h>
#include <fraber.h>
#include <hermer.h>
#include <tanker.h>
#include <wave.h>
#include <inputHandler.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <zapper.h>
#include <pulser.h>
#include <freezer.h>
#include <sniper.h>
#include <focuser.h>
#include <tower.h>
#include <string>
#include <upgradeMenu.h>
#include <buildMenu.h>
#include <random>
#include <stateInfoContainer.h>

class gameHandler
{
private:
    wave enemyWave;

    std::mt19937_64 gen = std::mt19937_64(12345);
    std::uniform_int_distribution<int> dis = std::uniform_int_distribution<int>(0,8);

    float addedTime = 0;
    float enemySpawnRate = 2.0f;
    float enemySpawnCooldown = 0;
    int amountSpawned = 0;

    int currentWaveSize = 8;

public:
    //Zapper Values
    float baseDamageZapper = 1;
    float baseSpeedZapper = 0.8f;
    float baseRangeZapper = 48;
    float baseCostZapper = 50;

    //Pulser Values
    float baseDamagePulser = 1;
    float baseSpeedPulser = 0.65f;
    float baseRangePulser = 64;
    float baseCostPulser = 150;

    //freezer Values
    float baseDamageFreezer = 1.5f;
    float baseSpeedFreezer = 1.2f;
    float baseRangeFreezer = 48;
    float baseCostFreezer = 150;

    //focuser Values
    float baseDamageFocuser = 0.2f;
    float baseSpeedFocuser = 2.5f;
    float baseRangeFocuser = 60;
    float baseCostFocuser = 200;

    //sniper Values
    float baseDamageSniper = 8;
    float baseSpeedSniper = 0.25f;
    float baseRangeSniper = 112;
    float baseCostSniper = 200;

    std::string message = "NULL";
    int messageTime = 0;

    bool buildMenuActive = false;
    bool upgradeMenuActive = false;

    upgradeMenu upgradeM;
    buildMenu buildM;

    int indexTowerHovered = -1;
    int indexTowerSelected = -1;

    int xTileSelected = -1;
    int yTileSelected = -1;
    
    void updateGameCooldowns(assets &rGameAsset, sf::Time elapsed);
    void generateWave(assets &rGameAsset);
    void updateWave(assets &rGameAsset);
    void spawnFraber(assets &rGameAsset, int wave);
    void spawnTanker(assets &rGameAsset, int wave);
    void spawnHermer(assets &rGameAsset, int wave);
    void placeTower(assets &rGameAsset, inputHandler &rInputH, sf::RenderWindow &rWindow);
    void updateHoveredTower(assets &rGameAsset, inputHandler &rInputH, sf::RenderWindow &rWindow);
    void updateSelectedTower(assets &rGameAsset, inputHandler &rInputH, sf::RenderWindow &rWindow);
    void updateSelectedTile(assets &rGameAsset, inputHandler &rInputH, sf::RenderWindow &rWindow);
    void checkMenuButtonPressed(assets &rGameAsset, inputHandler &rInputH, sf::RenderWindow &rWindow);
    void unselectEverything(inputHandler &rInputH);
    void checkCrystalIsDead(assets &rGameAsset, stateInfoContainer &rStateInfo);
};