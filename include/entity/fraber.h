#pragma once

#include <enemy.h>

class fraber : public enemy
{
private:
    /* data */
public:
    fraber(Eigen::Vector2f position, int wave);
};