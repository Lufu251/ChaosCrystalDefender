#pragma once

#include <attack.h>
#include <enemy.h>
#include <tower.h>
#include <vector>

class pulserAttack : public attack
{
private:
    /* data */
public:
    std::vector<enemy*> e;

    pulserAttack(tower* to, std::vector<enemy*> en) : e(en){
        t = to;
        e = en;
        type = "pulserAttack";
        currenttime = 0;
        maxTime = 0.5;
    }
};