#include <gameHandler.h>

void gameHandler::updateGameCooldowns(assets &rGameAsset, sf::Time elapsed){
    addedTime += elapsed.asSeconds();
    enemySpawnCooldown += elapsed.asSeconds();

    if(addedTime >= 1){
        if(rGameAsset.nextWave > 0){
            rGameAsset.nextWave --;
        }
        if(messageTime > 0){
            messageTime --;
        }
        addedTime = 0;
    }
    if(enemySpawnCooldown < enemySpawnRate){
        enemySpawnCooldown += elapsed.asSeconds();
    }
}
void gameHandler::generateWave(assets &rGameAsset){
    enemyWave.wave.clear();
    if(rGameAsset.waveCount < 5){
        // only fraber
        for (size_t i = 0; i < currentWaveSize; i++)
        {
            enemyWave.wave.push_back(FRABER);
        }
    }
    else if(rGameAsset.waveCount == 6){
        for (size_t i = 0; i < currentWaveSize; i++)
        {
            enemyWave.wave.push_back(FRABER);
        }
        enemyWave.wave[0] = HERMER;
        enemyWave.wave[2] = HERMER;
        enemyWave.wave[4] = HERMER;
        enemyWave.wave[6] = HERMER;
    }
    else if(rGameAsset.waveCount < 9){
        for (size_t i = 0; i < currentWaveSize; i++)
        {
            enemyWave.wave.push_back(FRABER);
        }
        enemyWave.wave[0] = HERMER;
        enemyWave.wave[2] = HERMER;
        enemyWave.wave[4] = HERMER;
        enemyWave.wave[6] = HERMER;
    }
    else if(rGameAsset.waveCount == 10){
        for (size_t i = 0; i < currentWaveSize; i++)
        {
            enemyWave.wave.push_back(FRABER);
        }
        enemyWave.wave[0] = TANKER;
        enemyWave.wave[2] = TANKER;
        enemyWave.wave[4] = TANKER;
        enemyWave.wave[6] = TANKER;
    }
    else {
        for (size_t i = 0; i < currentWaveSize; i++)
        {
            int rand = dis(gen);
            if(rand <= 2){
                enemyWave.wave.push_back(TANKER);
            }
            else if(rand <= 4){
                enemyWave.wave.push_back(FRABER);
            }
            else if(rand <= 8){
                enemyWave.wave.push_back(HERMER);
            }
        }
    }
}

void gameHandler::checkCrystalIsDead(assets &rGameAsset, stateInfoContainer &rStateInfo){
    if(rGameAsset.baseHealth <= 0){
        rStateInfo.setNextState(2);
    }
}

void gameHandler::updateWave(assets &rGameAsset){
    if(enemySpawnRate < enemySpawnCooldown && rGameAsset.nextWave == 0){
        if(amountSpawned < currentWaveSize){
            int e = enemyWave.wave[amountSpawned];
            if(e == FRABER){
                spawnFraber(rGameAsset, rGameAsset.waveCount);
            }
            else if(e == TANKER)
            {
                spawnTanker(rGameAsset, rGameAsset.waveCount);
            }
            else if(e == HERMER)
            {
                spawnHermer(rGameAsset, rGameAsset.waveCount);
            }
            amountSpawned ++;
        }
        else{
            amountSpawned = 0;
            rGameAsset.nextWave = 30;
            rGameAsset.waveCount ++;
            if (rGameAsset.waveCount % 3)
            currentWaveSize ++;

            generateWave(rGameAsset);
        }
    }
}

void gameHandler::spawnFraber(assets &rGameAsset, int wave){
        int realPosX = rGameAsset.grid.spawn.x() * rGameAsset.grid.tileSize + rGameAsset.grid.tileSize/2;
        int realPosY = rGameAsset.grid.spawn.y() * rGameAsset.grid.tileSize + rGameAsset.grid.tileSize/2;
        rGameAsset.enemys.push_back(std::make_unique<fraber>(Eigen::Vector2f(realPosX, realPosY), wave));
        enemySpawnCooldown = 0;
}

void gameHandler::spawnHermer(assets &rGameAsset, int wave){
        int realPosX = rGameAsset.grid.spawn.x() * rGameAsset.grid.tileSize + rGameAsset.grid.tileSize/2;
        int realPosY = rGameAsset.grid.spawn.y() * rGameAsset.grid.tileSize + rGameAsset.grid.tileSize/2;
        rGameAsset.enemys.push_back(std::make_unique<hermer>(Eigen::Vector2f(realPosX, realPosY), wave));
        enemySpawnCooldown = 0;
}

void gameHandler::spawnTanker(assets &rGameAsset, int wave){
        int realPosX = rGameAsset.grid.spawn.x() * rGameAsset.grid.tileSize + rGameAsset.grid.tileSize/2;
        int realPosY = rGameAsset.grid.spawn.y() * rGameAsset.grid.tileSize + rGameAsset.grid.tileSize/2;
        rGameAsset.enemys.push_back(std::make_unique<tanker>(Eigen::Vector2f(realPosX, realPosY), wave));
        enemySpawnCooldown = 0;
}

void gameHandler::updateHoveredTower(assets &rGameAsset, inputHandler &rInputH, sf::RenderWindow &rWindow){
    indexTowerHovered = -1;
    for (size_t i = 0; i < rGameAsset.towers.size(); i++)
    {
        tower* ct = rGameAsset.towers.at(i).get();
        int xMouse = rInputH.getMousePositionInRelationToView(rWindow).x();
        int yMouse = rInputH.getMousePositionInRelationToView(rWindow).y();
        if(xMouse >= ct->pos.x() -ct->size/2 && yMouse >= ct->pos.y() -ct->size/2 
        && xMouse <= ct->pos.x() + ct->size/2 && yMouse <= ct->pos.y() + ct->size/2){
            indexTowerHovered = int(i);
        }
    }
    
}

void gameHandler::updateSelectedTower(assets &rGameAsset, inputHandler &rInputH, sf::RenderWindow &rWindow){
    if(rInputH.isMousePressedOnce("left") == true){
        int xMouse = rInputH.getMousePositionInRelationToView(rWindow).x();
        int yMouse = rInputH.getMousePositionInRelationToView(rWindow).y();
        if(buildMenuActive == false){
            if(xMouse > upgradeM.pos.x() && yMouse > upgradeM.pos.y() && xMouse < upgradeM.pos.x() + upgradeM.size.x() && yMouse < upgradeM.pos.y() + upgradeM.size.y() && upgradeMenuActive == true){
            }
            else{
                // click is not inside of upgrade Menu
                indexTowerSelected = -1;
                upgradeMenuActive = false;
                for (size_t i = 0; i < rGameAsset.towers.size(); i++){
                    tower* ct = rGameAsset.towers.at(i).get();
                    if(xMouse >= ct->pos.x() -ct->size/2 && yMouse >= ct->pos.y() -ct->size/2 
                    && xMouse <= ct->pos.x() + ct->size/2 && yMouse <= ct->pos.y() + ct->size/2){

                        // activate upgradeMenu
                        indexTowerSelected = int(i);
                        upgradeMenuActive = true;
                        upgradeM = upgradeMenu(Eigen::Vector2i(xMouse, yMouse));
                    }
                }
            }
        }
    }
}

void gameHandler::updateSelectedTile(assets &rGameAsset, inputHandler &rInputH, sf::RenderWindow &rWindow){
    int xMouse = rInputH.getMousePositionInRelationToView(rWindow).x();
    int yMouse = rInputH.getMousePositionInRelationToView(rWindow).y();

    if(rInputH.isMousePressedOnce("left") == true){
        if(xMouse > buildM.pos.x() && yMouse > buildM.pos.y() && xMouse < buildM.pos.x() + buildM.size.x() && yMouse < buildM.pos.y() + buildM.size.y()  && buildMenuActive == true){
        }
        else{
            // click is not inside of build menu
            xTileSelected = -1;
            yTileSelected = -1;
            buildMenuActive = false;

            int xGridPos = xMouse / rGameAsset.grid.tileSize;
            int yGridPos = yMouse / rGameAsset.grid.tileSize;

            // click is inside of grid
            if(rInputH.getMousePositionInRelationToView(rWindow).x() > 0 
            && rInputH.getMousePositionInRelationToView(rWindow).y() > 0 
            && rInputH.getMousePositionInRelationToView(rWindow).x() < rGameAsset.grid.getSizeX() * rGameAsset.grid.tileSize
            && rInputH.getMousePositionInRelationToView(rWindow).y() < rGameAsset.grid.getSizeY() * rGameAsset.grid.tileSize){
                if(rGameAsset.grid(xGridPos, yGridPos).blocking == true){
                    // placement is not possible
                }
                else if(indexTowerSelected == -1){
                    if(xGridPos == rGameAsset.grid.base.x() && yGridPos == rGameAsset.grid.base.y() 
                    || xGridPos == rGameAsset.grid.spawn.x() && yGridPos == rGameAsset.grid.spawn.y()){
                        std::cout << "tower placement not allowed because it is a spawn or base Point" << std::endl;
                        message = "tower placement not possible";
                        messageTime = 2;
                    }
                    else{
                        rGameAsset.grid(xGridPos, yGridPos).blocking = true;
                        rGameAsset.grid.calculateFlowfield();
                        if(rGameAsset.grid(rGameAsset.grid.spawn.x(), rGameAsset.grid.spawn.y()).cost == 10000){
                            // not allowed tower placement because path is blocked
                            std::cout << "tower placement not allowed because path is blocked" << std::endl;
                            message = "tower placement not possible";
                            messageTime = 2;


                        }
                        else{
                            xTileSelected = xGridPos;
                            yTileSelected = yGridPos;
                            
                            buildMenuActive = true;
                            buildM = buildMenu(Eigen::Vector2i(xMouse, yMouse));
                        }
                        rGameAsset.grid(xGridPos, yGridPos).blocking = false;
                        rGameAsset.grid.calculateFlowfield();
                    }
                }
            }
        }
    }
}

void gameHandler::checkMenuButtonPressed(assets &rGameAsset, inputHandler &rInputH, sf::RenderWindow &rWindow){
    int xMouse = rInputH.getMousePositionInRelationToView(rWindow).x();
    int yMouse = rInputH.getMousePositionInRelationToView(rWindow).y();
    if(buildMenuActive == true){
        for (size_t i = 0; i < buildM.buttons.size(); i++)
        {
            if(rInputH.isMousePressedOnce("left") == true){
                if(xMouse > buildM.buttons.at(i).pos.x() && yMouse > buildM.buttons.at(i).pos.y() 
                && xMouse < buildM.buttons.at(i).pos.x() + buildM.buttons.at(i).sizeX && yMouse < buildM.buttons.at(i).pos.y() + buildM.buttons.at(i).sizeY){
                    std::string type = buildM.buttons.at(i).action;

                    int xBuildPos = xTileSelected * rGameAsset.grid.tileSize + rGameAsset.grid.tileSize/2;
                    int yBuildPos = yTileSelected * rGameAsset.grid.tileSize + rGameAsset.grid.tileSize/2;
                    bool placed = false;
                    if(type == "zapper" && rGameAsset.money >= baseCostZapper){
                        rGameAsset.money -= int(baseCostZapper);
                        rGameAsset.towers.push_back(std::make_unique<zapper>(Eigen::Vector2f(xBuildPos, yBuildPos), baseDamageZapper, baseSpeedZapper, baseRangeZapper, baseCostZapper));
                        placed = true;
                    }
                    else if(type == "pulser" && rGameAsset.money >= baseCostPulser){
                        rGameAsset.money -= int(baseCostPulser);
                        rGameAsset.towers.push_back(std::make_unique<pulser>(Eigen::Vector2f(xBuildPos, yBuildPos), baseDamagePulser, baseSpeedPulser, baseRangePulser, baseCostPulser));
                        placed = true;
                    }
                    else if(type == "freezer" && rGameAsset.money >= baseCostFreezer){
                        rGameAsset.money -= int(baseCostFreezer);
                        rGameAsset.towers.push_back(std::make_unique<freezer>(Eigen::Vector2f(xBuildPos, yBuildPos), baseDamageFreezer, baseSpeedFreezer, baseRangeFreezer, baseCostFreezer));
                        placed = true;
                    }
                    else if(type == "focuser" && rGameAsset.money >= baseCostFocuser){
                        rGameAsset.money -= int(baseCostFocuser);
                        rGameAsset.towers.push_back(std::make_unique<focuser>(Eigen::Vector2f(xBuildPos, yBuildPos), baseDamageFocuser, baseSpeedFocuser, baseRangeFocuser, baseCostFocuser));
                        placed = true;
                    }
                    else if(type == "sniper" && rGameAsset.money >= baseCostSniper){
                        rGameAsset.money -= int(baseCostSniper);
                        rGameAsset.towers.push_back(std::make_unique<sniper>(Eigen::Vector2f(xBuildPos, yBuildPos), baseDamageSniper, baseSpeedSniper, baseRangeSniper, baseCostSniper));
                        placed = true;
                    }
                    
                    if(placed){
                        rGameAsset.grid(xTileSelected, yTileSelected).blocking = true;
                        rGameAsset.grid.calculateFlowfield();
                        xTileSelected = -1;
                        yTileSelected = -1;
                        buildMenuActive = false;
                    }
                    else{
                        message = "not enough money";
                        messageTime = 2;
                    }
                }
            }
        }
        
    }

    if(upgradeMenuActive == true){
        for (size_t i = 0; i < upgradeM.buttons.size(); i++)
        {
            if(rInputH.isMousePressedOnce("left") == true){
                if(xMouse > upgradeM.buttons.at(i).pos.x() && yMouse > upgradeM.buttons.at(i).pos.y() 
                && xMouse < upgradeM.buttons.at(i).pos.x() + upgradeM.buttons.at(i).sizeX && yMouse < upgradeM.buttons.at(i).pos.y() + upgradeM.buttons.at(i).sizeY){
                    std::string type = upgradeM.buttons.at(i).action;
                    bool done = false;
                    if(type == "upgrade" && rGameAsset.money >= rGameAsset.towers.at(indexTowerSelected)->currentCost + rGameAsset.towers.at(indexTowerSelected)->costAdd){
                        rGameAsset.money -= rGameAsset.towers.at(indexTowerSelected)->currentCost + int(rGameAsset.towers.at(indexTowerSelected)->costAdd);
                        rGameAsset.towers.at(indexTowerSelected)->level ++;
                        rGameAsset.towers.at(indexTowerSelected)->attackSpeed += rGameAsset.towers.at(indexTowerSelected)->speedUpgrade;
                        rGameAsset.towers.at(indexTowerSelected)->currentCost += int(rGameAsset.towers.at(indexTowerSelected)->costAdd);
                        rGameAsset.towers.at(indexTowerSelected)->damage += rGameAsset.towers.at(indexTowerSelected)->damageUpgrade;
                        rGameAsset.towers.at(indexTowerSelected)->range += rGameAsset.towers.at(indexTowerSelected)->rangeUpgrade;
                        done = true;
                    }
                    else if(type == "sell"){
                        rGameAsset.money += int(rGameAsset.towers.at(indexTowerSelected)->currentCost /2);
                        int xGrid = int(rGameAsset.towers.at(indexTowerSelected)->pos.x() / rGameAsset.grid.tileSize);
                        int yGrid = int(rGameAsset.towers.at(indexTowerSelected)->pos.y() / rGameAsset.grid.tileSize);
                        rGameAsset.grid(xGrid, yGrid).blocking = false;
                        rGameAsset.grid.calculateFlowfield();
                        rGameAsset.towers.erase(rGameAsset.towers.begin() + indexTowerSelected);
                        indexTowerHovered = -1;
                        done = true;
                    }
                    if(done){
                        indexTowerSelected = -1;
                        upgradeMenuActive = false;
                    }
                    else{
                        message = "not enough money";
                        messageTime = 2;
                    }
                }
            }
        }
    }
}

void gameHandler::unselectEverything(inputHandler &rInputH){
    if(rInputH.isMousePressedOnce("right") == true){
        xTileSelected = -1;
        yTileSelected = -1;
        upgradeMenuActive = false;
        buildMenuActive = false;
        indexTowerSelected = -1;
    }
}