#include <enemyHandler.h>

void enemyHandler::moveEnemys(std::vector<std::unique_ptr<enemy>>& rEnemys, tileGrid& rGrid, sf::Time& rElapsed){
    
    for (size_t i = 0; i < rEnemys.size(); i++)
    {
        // check which node is next
        bool top = false;
        bool down = false;
        bool left = false;
        bool right = false;
        Eigen::Vector2f steeringPoint(0,0);
        Eigen::Vector2f moveDirection(0,0);

        int gridPosX = int(rEnemys.at(i)->pos.x() / rGrid.tileSize);
        int gridPosY = int(rEnemys.at(i)->pos.y() / rGrid.tileSize);
        int currentCost = rGrid(gridPosX, gridPosY).cost;

        int margin = 2;

        // top
        if(gridPosY -1 >= 0 && rGrid(gridPosX, gridPosY -1).cost < currentCost){
            top = true;
            steeringPoint = {gridPosX * rGrid.tileSize + rGrid.tileSize/2, 
                            (gridPosY) * rGrid.tileSize -margin};
            moveDirection = steeringPoint - rEnemys.at(i)->pos;

            // update cost and progression from enemy
            float prog = float(std::fmod(rEnemys.at(i)->pos.y(), rGrid.tileSize) / rGrid.tileSize);
            rEnemys.at(i)->progression = rGrid(gridPosX, gridPosY).cost + prog;
        }

        // down
        else if(gridPosY +1 < rGrid.getSizeY() && rGrid(gridPosX, gridPosY +1).cost < currentCost){
            down = true;
            steeringPoint = {gridPosX * rGrid.tileSize + rGrid.tileSize/2, 
                            (gridPosY +1) * rGrid.tileSize +margin};
            moveDirection = steeringPoint - rEnemys.at(i)->pos;

            // update cost and progression from enemy
            float prog = 1 - float(std::fmod(rEnemys.at(i)->pos.y(), rGrid.tileSize) / rGrid.tileSize);
            rEnemys.at(i)->progression = rGrid(gridPosX, gridPosY).cost + prog;
        }

        // right
        else if(gridPosX +1 < rGrid.getSizeX() && rGrid(gridPosX +1, gridPosY).cost < currentCost){
            right = true;
            steeringPoint = {(gridPosX +1) * rGrid.tileSize + margin, 
                            gridPosY * rGrid.tileSize + rGrid.tileSize/2};
            moveDirection = steeringPoint - rEnemys.at(i)->pos;

            // update cost and progression from enemy
            float prog = 1 - float(std::fmod(rEnemys.at(i)->pos.x(), rGrid.tileSize) / rGrid.tileSize);
            rEnemys.at(i)->progression = rGrid(gridPosX, gridPosY).cost + prog;
        }

        // left
        else if(gridPosX -1 >= 0 && rGrid(gridPosX -1, gridPosY).cost < currentCost){
            left = true;
            steeringPoint = {(gridPosX) * rGrid.tileSize - margin,
                            gridPosY  * rGrid.tileSize + rGrid.tileSize/2};
            moveDirection = steeringPoint - rEnemys.at(i)->pos;

            // update cost and progression from enemy
            float prog = float(std::fmod(rEnemys.at(i)->pos.x(), rGrid.tileSize) / rGrid.tileSize);
            rEnemys.at(i)->progression = rGrid(gridPosX, gridPosY).cost + prog;
        }

        // apply forces
        moveDirection.normalize();
        moveDirection *= rEnemys.at(i)->speed;
        if(rEnemys.at(i)->freezed == true){
            moveDirection *= rEnemys.at(i)->freezeStrength;
        }
        moveDirection *= rElapsed.asSeconds();
        rEnemys.at(i)->pos += moveDirection;
    }
    
}

void enemyHandler::isAtBase(assets& rGameAsset){
    for (size_t i = 0; i < rGameAsset.enemys.size(); i++)
    {
        int gridPosX = int(rGameAsset.enemys.at(i)->pos.x() / rGameAsset.grid.tileSize);
        int gridPosY = int(rGameAsset.enemys.at(i)->pos.y() / rGameAsset.grid.tileSize);
        if(gridPosX == rGameAsset.grid.base.x() && gridPosY == rGameAsset.grid.base.y()){
            rGameAsset.enemys[i]->isDead = true;
            rGameAsset.baseHealth --;
        }
    }
}

void enemyHandler::removeDead(assets &rGameAsset){
    for (size_t i = 0; i < rGameAsset.enemys.size(); i++)
    {
        if(rGameAsset.enemys[i]->isDead == true){

            if(rGameAsset.enemys[i]->currentHealth <= 0){
                // add money
                int moneyAdd;
                moneyAdd = int(std::sqrt(float(rGameAsset.waveCount))* 3.5 +2.5);
                rGameAsset.money += moneyAdd;
            }
            std::swap(rGameAsset.enemys[i], rGameAsset.enemys.back());
            rGameAsset.enemys.pop_back();
            i--;
        }
    }
}

void enemyHandler::updateStatus(assets& rGameAsset, sf::Time elapsed){
    for (size_t i = 0; i < rGameAsset.enemys.size(); i++)
    {
        if(rGameAsset.enemys[i]->freezeTime > 0){
            rGameAsset.enemys[i]->freezeTime -= elapsed.asSeconds();
        }

        if(rGameAsset.enemys[i]->freezeTime <= 0 && rGameAsset.enemys[i]->freezed == true){
            rGameAsset.enemys[i]->freezed = false;
            rGameAsset.enemys[i]->freezeTime = 0;
             rGameAsset.enemys[i]->freezeStrength = 0;
        }
        
        if(rGameAsset.enemys[i]->targetTime > 0){
            rGameAsset.enemys[i]->targetTime -= elapsed.asSeconds();
        }

        if(rGameAsset.enemys[i]->targetTime <= 0 && rGameAsset.enemys[i]->targeted == true){
            rGameAsset.enemys[i]->targeted = false;
            rGameAsset.enemys[i]->targetTime = 0;
             rGameAsset.enemys[i]->targetStrength = 0;
        }
    }
    
}