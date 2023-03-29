#include <attackHandler.h>

void attackHandler::updateTime(assets &rGameAsset, sf::Time elapsed){
    for (size_t i = 0; i < rGameAsset.attacks.size(); i++)
    {
        rGameAsset.attacks.at(i)->currenttime += elapsed.asSeconds();
    }
}

void attackHandler::checkTime(assets &rGameAsset){
    for (size_t i = 0; i < rGameAsset.attacks.size(); i++)
    {
        // time is over
        if (rGameAsset.attacks.at(i)->currenttime >= rGameAsset.attacks.at(i)->maxTime)
        {
            rGameAsset.attacks[i]->isDead = true;
        }
    }
}

void attackHandler::removeDeadAttacks(assets &rGameAsset){
    for (size_t i = 0; i < rGameAsset.attacks.size(); i++)
    {
        if(rGameAsset.attacks[i]->isDead == true){
            std::swap(rGameAsset.attacks[i], rGameAsset.attacks.back());
            rGameAsset.attacks.pop_back();
            i--;
        }
    }
}

void attackHandler::checkDeadEnemyAndSetLastEnemyPosition(assets &rGameAsset){

    for (size_t i = 0; i < rGameAsset.attacks.size(); i++)
    {

        // check if targeted enemy is dead;
        std::string type = rGameAsset.attacks[i]->type;
        if(type == "zapperAttack"){
            zapperAttack* a = static_cast<zapperAttack*>(rGameAsset.attacks[i].get());
            
            // check if enemy is already dead
            if(a->e->isDead == true && a->enemyIsDead == false){
                a->lastEnemyPosition.x = a->e->pos.x();
                a->lastEnemyPosition.y = a->e->pos.y();
                a->enemyIsDead =  true;
            }
        }
        else if(type == "sniperAttack"){
            sniperAttack* a = static_cast<sniperAttack*>(rGameAsset.attacks[i].get());

            // check if enemy is already dead
            if(a->e->isDead == true && a->enemyIsDead == false){
                a->lastEnemyPosition.x = a->e->pos.x();
                a->lastEnemyPosition.y = a->e->pos.y();
                a->enemyIsDead =  true;
            }
        }
        else if(type == "focuserAttack"){
            focuserAttack* a = static_cast<focuserAttack*>(rGameAsset.attacks[i].get());

            // check if enemy is already dead
            if(a->e->isDead == true && a->enemyIsDead == false){
                a->lastEnemyPosition.x = a->e->pos.x();
                a->lastEnemyPosition.y = a->e->pos.y();
                a->enemyIsDead =  true;
            }
        }
    }
}

void attackHandler::doDamage(assets &rGameAsset){
    
    for (size_t i = 0; i < rGameAsset.attacks.size(); i++)
    {
        if(rGameAsset.attacks[i]->damage == true){

            std::string type = rGameAsset.attacks[i]->type;

            if(type == "zapperAttack"){
                zapperAttack* a = static_cast<zapperAttack*>(rGameAsset.attacks[i].get());
                if(a->e->isDead == false){
                    // calculate damage and deal damage
                    float damage = a->t->damage;
                    if(a->e->targeted){
                        damage *= a->e->targetStrength;
                    }
                    a->e->currentHealth -= damage;

                    // check if the enemy died after the attack
                    if(a->e->currentHealth <= 0){
                        a->e->isDead = true;
                        a->enemyIsDead = true;
                    }
                }
                else{
                    // the enemy was already dead befor it was attacked
                    a->t->cooldown = a->t->attackSpeed;
                    a->isDead = true;
                }
            }
            else if(type == "pulserAttack"){
                pulserAttack* a = static_cast<pulserAttack*>(rGameAsset.attacks[i].get());
                for (size_t i = 0; i < a->e.size(); i++)
                {
                    float damage = a->t->damage;
                    if(a->e[i]->targeted){
                        damage *= a->e[i]->targetStrength;
                    }
                    a->e[i]->currentHealth -= damage;
                    // check if the enemy died
                    if(a->e[i]->currentHealth <= 0){
                        a->e[i]->isDead = true;
                    }
                }
            }
            else if(type == "freezerAttack"){
                freezerAttack* a = static_cast<freezerAttack*>(rGameAsset.attacks[i].get());
                for (size_t i = 0; i < a->e.size(); i++)
                {
                    a->e[i]->freezed = true;
                    float freezeStrength = 0.8f - a->t->damage / (1 + 6 * a->t->damage);
                    a->e[i]->freezeStrength = freezeStrength;
                    a->e[i]->freezeTime = a->t->damage;
                }
            }
            else if(type == "sniperAttack"){
                sniperAttack* a = static_cast<sniperAttack*>(rGameAsset.attacks[i].get());
                if(a->e->isDead == false){
                    float damage = a->t->damage;
                    if(a->e->targeted){
                        damage *= a->e->targetStrength;
                    }
                    a->e->currentHealth -= damage;

                    a->e->targeted = true;
                    a->e->targetStrength = 1.25;
                    a->e->targetTime = 3;

                    // check if the enemy died after the attack
                    if(a->e->currentHealth <= 0){
                        a->e->isDead = true;
                        a->enemyIsDead = true;
                    }
                }
                else{
                    // the enemy was already dead befor it was attacked
                    a->t->cooldown = a->t->attackSpeed;
                    a->isDead = true;
                }
            }

            else if(type == "focuserAttack"){
                focuserAttack* a = static_cast<focuserAttack*>(rGameAsset.attacks[i].get());
                focuser* f = static_cast<focuser*>(a->t);
                if(a->e->isDead == false){
                    if(f->lastEnemy == a->e){
                        // is the same enemy as last time;
                        f->addedDamage *= 2;
                    }
                    else{
                        f->addedDamage = f->damage;
                        a->isDead = true; // destroy attack on switch enemy
                    }

                    //cap damage
                    f->addedDamage = std::min(f->addedDamage, f->damage * 60.0f +4);
                    float damage = f->addedDamage;

                    if(a->e->targeted){
                        damage *= a->e->targetStrength;
                    }
                    a->e->currentHealth -= damage;
                    f->lastEnemy = a->e;

                    // check if the enemy died after the attack
                    if(a->e->currentHealth <= 0){
                        a->isDead = true; //special because it needs to be destroyed on died enemy
                        a->e->isDead = true;
                    }
                }
                else{
                    // the enemy was already dead befor it was attacked
                    a->t->cooldown = a->t->attackSpeed;
                    a->isDead = true;
                }
            }
            rGameAsset.attacks[i]->damage = false;
        }
    }
}