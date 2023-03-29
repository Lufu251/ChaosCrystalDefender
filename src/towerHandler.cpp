#include <towerHandler.h>

void towerHandler::updateCooldown(std::vector<std::unique_ptr<tower>>& rTowers, sf::Time &rDelta){
    for (size_t i = 0; i < rTowers.size(); i++){
        if(rTowers.at(i)->cooldown <= 1.0f / rTowers.at(i)->attackSpeed)
        {
            rTowers.at(i)->cooldown += rDelta.asSeconds();
        }
    }
}

std::vector<int> towerHandler::getEnemysToAttackSorted(tower* currentTower, assets &rGameAsset){
    float currentMinCost = 10000;

    // fill index vector with amount of indexes in enemy vector
    std::vector<int> possibleEnemys;
    for (size_t m = 0; m < rGameAsset.enemys.size(); m++){
        possibleEnemys.push_back(int(m));
    }

    // iterate indexes of enemys
    for (size_t j = 0; j < possibleEnemys.size(); j++)
    {
        int n = possibleEnemys.at(j); // translate

        // remove all enemys outside of tower range or enemys that are already dead
        Eigen::Vector2f distance = currentTower->pos - rGameAsset.enemys.at(n)->pos;
        float distanceSquared = distance.squaredNorm();
        if(currentTower->range * currentTower->range <= distanceSquared || rGameAsset.enemys[possibleEnemys[j]]->isDead == true){
            // enemy is out of range
            std::swap(possibleEnemys[j], possibleEnemys.back());
            possibleEnemys.pop_back();
            j--;
        }
    }

    std::sort(possibleEnemys.begin(), possibleEnemys.end(), [&](int a, int b){return rGameAsset.enemys.at(a)->progression < rGameAsset.enemys.at(b)->progression;});

    return possibleEnemys;
}

void towerHandler::attack(assets &rGameAsset){
    
    for (size_t i = 0; i < rGameAsset.towers.size(); i++)
    {
        tower* currentTower = rGameAsset.towers.at(i).get();

        // check if tower is ready to attack and if any enemy is on the field
        if(rGameAsset.towers.at(i)->cooldown >= 1.0f / rGameAsset.towers.at(i)->attackSpeed){

            std::vector<int> enemysToAttack = getEnemysToAttackSorted(currentTower, rGameAsset);
            if(enemysToAttack.size() > 0){
                if(currentTower->type == "zapper"){
                    enemy* currentEnemy = rGameAsset.enemys.at(enemysToAttack.at(0)).get();
                    rGameAsset.attacks.push_back(std::make_unique<zapperAttack>(currentTower, currentEnemy));
                    
                    currentTower->attackedEnemy = currentEnemy;
                }
                else if(currentTower->type == "pulser"){
                    std::vector<enemy*> currentEnemys;
                    for (size_t i = 0; i < enemysToAttack.size(); i++)
                    {
                        currentEnemys.push_back(rGameAsset.enemys.at(enemysToAttack.at(i)).get());
                    }
                    rGameAsset.attacks.push_back(std::make_unique<pulserAttack>(currentTower, currentEnemys));
                }
                else if(currentTower->type == "freezer"){
                    std::vector<enemy*> currentEnemys;
                    for (size_t i = 0; i < enemysToAttack.size(); i++)
                    {
                        currentEnemys.push_back(rGameAsset.enemys.at(enemysToAttack.at(i)).get());
                    }
                    rGameAsset.attacks.push_back(std::make_unique<freezerAttack>(currentTower, currentEnemys));
                }
                else if(currentTower->type == "sniper"){
                    enemy* currentEnemy = rGameAsset.enemys.at(enemysToAttack.at(0)).get();
                    rGameAsset.attacks.push_back(std::make_unique<sniperAttack>(currentTower, currentEnemy));
                    currentTower->attackedEnemy = currentEnemy;
                }
                else if(currentTower->type == "focuser"){
                    enemy* currentEnemy = rGameAsset.enemys.at(enemysToAttack.at(0)).get();
                    rGameAsset.attacks.push_back(std::make_unique<focuserAttack>(currentTower, currentEnemy));
                    currentTower->attackedEnemy = currentEnemy;
                }
                currentTower->cooldown = 0;
            }
            else{
                currentTower->attackedEnemy = nullptr;
            }
        }
    }
    
}

void towerHandler::checkAttackedEnemyIsDead(assets &rGameAsset){
    for (size_t i = 0; i < rGameAsset.towers.size(); i++){

        tower* currentTower = rGameAsset.towers.at(i).get();
        if(currentTower->attackedEnemy != nullptr){
            if(currentTower->attackedEnemy->isDead){
                currentTower->attackedEnemy = nullptr;
            }
        }
    }
}

void towerHandler::calculateRotation(assets &rGameAsset){
    for (size_t i = 0; i < rGameAsset.towers.size(); i++)
    {
        tower* currentTower = rGameAsset.towers.at(i).get();
        if(currentTower->attackedEnemy != nullptr){
            if(currentTower->attackedEnemy->currentHealth > 0){
            float calculatedRotation = atan2(currentTower->pos.x() - currentTower->attackedEnemy->pos.x(), currentTower->pos.y() - currentTower->attackedEnemy->pos.y());

            currentTower->rotation = float(360 - calculatedRotation  * 180 / M_PI);
            }
        }
    }
}