#pragma once

#include <attack.h>
#include <enemy.h>
#include <tower.h>
#include <vector>

class freezerAttack : public attack
{
private:
    /* data */
public:
    std::vector<enemy*> e;

    freezerAttack(tower* to, std::vector<enemy*> en){
        t = to;
        e = en;
        type = "freezerAttack";
        currenttime = 0;
        maxTime = 0.5;
    }
};