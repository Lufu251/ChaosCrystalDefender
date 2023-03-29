#pragma once

#include <enemy.h>

class tanker : public enemy
{
private:
    /* data */
public:
    tanker(Eigen::Vector2f position, int wave);
};